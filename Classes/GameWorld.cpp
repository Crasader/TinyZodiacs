//
//  GameWorld.cpp
//  Headball
//
//  Created by Nhut on 3/10/14.
//
//

#include "GameWorld.h"
#include "GLES-Render.h"
#include "ObjectFactory.h"
#include "MapCreator.h"
#include "MapObjectDTO.h"
#include "MapFactory.h"
#include "GameBackgroundLayer.h"
#include "LayerIndexConstants.h"
#include "GameObjectView.h"
#include "InfoViewCreator.h"
#include "Util.h"
#include "MonsterFactory.h"
#include "ActionZoomFollow.h"

GameWorld::GameWorld()
{
    this->width = 0;
    this->height = 0;
    this->world = NULL;
    this->map = NULL;
    this->group1 = NULL;
    this->group2 = NULL;    this->cameraFollowAction = NULL;
    
}

GameWorld::~GameWorld()
{
    delete this->world;
    this->world = NULL;
    
    GameHolder holder;
    holder.worldHolder = NULL;
    holder.nodeHolder = NULL;
    GameManager::getInstance()->setGameplayHolder(holder);
}

bool GameWorld::init()
{
    this->scheduleUpdate();
    //
    //    CCArray* arr = CCArray::create();
    //    arr->addObject(CCDelayTime::create(10));
    //    arr->addObject(CCCallFunc::create(this, callfunc_selector (GameWorld::foo)));
    //
    //    CCSequence* seq = CCSequence::create(arr);
    //    this->runAction(CCRepeatForever::create(seq));
    return true;
}

void GameWorld::onCreate()
{
    onCreateWorld();
    onCreateMap();
    
    // init gameholder
    GameHolder gameplayholder;
    gameplayholder.nodeHolder = this->map;
    gameplayholder.worldHolder = this->world;
    GameManager::getInstance()->setGameplayHolder(gameplayholder);

    onCreateUnits();
    
      //
    //    this->setCameraFollowGroup(this->group1);
    //
    //
    addManager();
    
}
void GameWorld::onCreateMap()
{
    MapCreator* mapCreator = new MapCreator();
    map = mapCreator->createMap(this->mapID.c_str(),this);
    delete mapCreator;
    
    this->map->attachAllMapObject();
    this->addChild(map, MAP_LAYER);
}
void GameWorld::onCreateWorld()
{
    b2Vec2 gravity = b2Vec2(GRAVITY_ACCELERATION_X, GRAVITY_ACCELERATION_Y);
    this->world = new b2World(gravity);
    //Set contact listener
    this->setContactListener(this);
    
    createWorldBox();
    
    //DEBUG WORLD
    b2Draw* _debugDraw = new GLESDebugDraw(PTM_RATIO);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    //    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
    this->world->SetDebugDraw(_debugDraw);
}

void GameWorld::onCreateUnits()
{
    this->group1 = GameGroup::create();
    this->group1->retain();
    this->group1->joinGame(A, this->world, this->map);
    
    this->group2 = GameGroup::create();
    this->group2->retain();
    this->group2->joinGame(B, this->world, this->map);
}

void GameWorld::addHero(MainHero* hero)
{
    if(hero != NULL)
    {
        hero->setRevivePosition(ccp(this->map->getMapDTO()->revivePositionX, this->map->getMapDTO()->revivePositionY));
        hero->setPositionInPixel(ccp(this->map->getMapDTO()->revivePositionX, this->map->getMapDTO()->revivePositionY));
        hero->attachSpriteTo(this->map);
        setCameraFollowNode(hero->getSprite());
    }
}


void GameWorld::addManager()
{
    GameHolder holder;
    holder.nodeHolder = this->map;
    holder.worldHolder = this->world;
    
    GameManager::getInstance()->setGameplayHolder(holder);
    EffectManager::getInstance()->setHolder(GameManager::getInstance()->getGameplayHolder());
    ItemFactory::getInstance()->setIsActive(true);
    ItemFactory::getInstance()->setHolder(GameManager::getInstance()->getGameplayHolder());
}


void GameWorld::createWorldBox()
{
    //set ground bot
    b2BodyDef bottomGroundBodyDef;
    bottomGroundBodyDef.type = b2_staticBody;
    bottomGroundBodyDef.position.Set((left+0)/PTM_RATIO, (bottom+0)/PTM_RATIO);
    
    
    this->bottomLine = this->world->CreateBody(&bottomGroundBodyDef);
    b2EdgeShape bottomEdgeShape;
    b2FixtureDef bottomFixtureDef;
    bottomFixtureDef.shape = &bottomEdgeShape;
    bottomFixtureDef.friction=0.5;
    bottomFixtureDef.filter.maskBits = 0xFFFFFF;
    bottomFixtureDef.filter.categoryBits = GROUP_TERRAIN;
    
    bottomEdgeShape.Set(b2Vec2(0, 0), b2Vec2(this->width/PTM_RATIO,0));
    this->bottomLine->CreateFixture(&bottomFixtureDef);
    
    //set ground top
    b2BodyDef topGroundBodyDef;
    topGroundBodyDef.type = b2_staticBody;
    topGroundBodyDef.position.Set((left)/PTM_RATIO, (bottom + this->height)/PTM_RATIO);
    
    
    this-> topLine = this->world->CreateBody(&topGroundBodyDef);
    b2EdgeShape topEdgeShape;
    b2FixtureDef topFixtureDef;
    topFixtureDef.shape = &topEdgeShape;
    topFixtureDef.friction=0.5;
    topFixtureDef.filter.maskBits = 0xFFFFFF;
    topFixtureDef.filter.categoryBits = GROUP_TERRAIN;
    
    topEdgeShape.Set(b2Vec2(0, 0), b2Vec2(this->width/PTM_RATIO,0));
    this-> topLine ->CreateFixture(&topFixtureDef);
    
    //set ground left
    b2BodyDef leftGroundBodyDef;
    leftGroundBodyDef.type = b2_staticBody;
    leftGroundBodyDef.position.Set((this->left+0)/PTM_RATIO, (this->bottom+0)/PTM_RATIO);
    
    
    this->leftLine = this->world->CreateBody(&leftGroundBodyDef);
    b2EdgeShape leftEdgeShape;
    b2FixtureDef leftFixtureDef;
    leftFixtureDef.shape = &leftEdgeShape;
    leftFixtureDef.friction=0.5;
    leftFixtureDef.filter.maskBits = 0xFFFFFF;
    leftFixtureDef.filter.categoryBits = GROUP_TERRAIN;
    
    leftEdgeShape.Set(b2Vec2(0, 0), b2Vec2(0,(this->height)/PTM_RATIO));
    this->leftLine->CreateFixture(&leftFixtureDef);
    
    //set ground right
    b2BodyDef rightGroundBodyDef;
    rightGroundBodyDef.type = b2_staticBody;
    rightGroundBodyDef.position.Set((left+this->width)/PTM_RATIO,(bottom+0)/PTM_RATIO);
    
    this->rightLine = this->world->CreateBody(&rightGroundBodyDef);
    b2EdgeShape rightEdgeShape;
    b2FixtureDef rightFixtureDef;
    rightFixtureDef.shape = &rightEdgeShape;
    rightFixtureDef.friction=0.5;
    rightFixtureDef.filter.maskBits = 0xFFFFFF;
    rightFixtureDef.filter.categoryBits = GROUP_TERRAIN;
    
    rightEdgeShape.Set(b2Vec2(0, 0), b2Vec2(0/PTM_RATIO,this->height/PTM_RATIO));
    this->rightLine->CreateFixture(&rightFixtureDef);
    
}

void GameWorld::setContactListener(b2ContactListener *listener)
{
    if(this->world != NULL)
    {
        this->world->SetContactListener(listener);
    }
}

void GameWorld::update(float dt)
{
    GameObjectManager::getInstance()->update(dt);
    this->map->update(dt);
    this->group1->update(dt);
    this->group2->update(dt);
    
    if(this->world != NULL)
    {
        world->Step(1/40.000f,8, 3);
    }

}

void GameWorld::destroy()
{
    GameObjectManager::getInstance()->removeAllGameObject();
}

void GameWorld::draw()
{
//
//        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//       kmGLPushMatrix();
//        world->DrawDebugData();
//       kmGLPopMatrix();

}

void GameWorld::setCameraFollowGroup(GameGroup* group)
{
    if(group == NULL)
    {
        if(this->cameraFollowAction != NULL)
        {
            
            this->stopAction(this->cameraFollowAction);
            
        }
        return;
    }
    
    if(group->getFollowingCharacter() == NULL)
    {
        return;
    }
    setCameraFollowNode(group->getFollowingCharacter()->getSprite());
    
}

void GameWorld::setCameraFollowNode(CCNode* nodeFollowed)
{
    if(this->cameraFollowAction != NULL)
    {
        this->stopAction(this->cameraFollowAction);
    }
    this->cameraFollowAction = CCFollow::create(nodeFollowed,CCRect(0, 0, this->width, this->height));
    
    this->runAction(this->cameraFollowAction);
}
//PHYSICS CONTACT
void GameWorld::BeginContact(b2Contact *contact)
{
    GameObjectManager::getInstance()->BeginContact(contact);
}

void GameWorld::EndContact(b2Contact *contact)
{
    GameObjectManager::getInstance()->EndContact(contact);
}

void GameWorld::foo()
{
    this->group1->test();
}

