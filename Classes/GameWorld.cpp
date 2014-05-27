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
}

GameWorld::~GameWorld()
{
    
}

bool GameWorld::init()
{
    count = 0;
    b2Vec2 gravity = b2Vec2(GRAVITY_ACCELERATION_X, GRAVITY_ACCELERATION_Y);
    this->world = new b2World(gravity);
    
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
    //Set contact listener
    this->setContactListener(this);
  
    //MAP
    MapCreator* mapCreator = new MapCreator();
    map = mapCreator->createMap("map1",this);
    map->attachAllMapObject();
   
    this->addChild(map,MAP_LAYER);
    
    delete mapCreator;
    
    GameHolder gameplayholder;
    gameplayholder.nodeHolder = this->map;
    gameplayholder.worldHolder = this->world;
    
    GameManager::getInstance()->setGameplayHolder(gameplayholder);
    
    
    createWorldBox();
  
    this->group1 = GameGroup::create();
    this->group1->retain();
    this->group1->joinGame(A, this->world, this->map);
    
    this->group2 = GameGroup::create();
    this->group2->retain();
    this->group2->joinGame(B, this->world, this->map);
    
    
    CCArray* arr = CCArray::create();
    arr->addObject(CCDelayTime::create(10));
    arr->addObject(CCCallFunc::create(this, callfunc_selector (GameWorld::foo)));
    
    CCSequence* seq = CCSequence::create(arr);
    this->runAction(CCRepeatForever::create(seq));
    
    this->setCameraFollowGroup(this->group1);
    
    addManager();
    return true;
}


void GameWorld::addManager()
{
    this->addChild(ScheduleManager::getInstance());
    this->addChild(GameObjectManager::getInstance());
    this->addChild(EffectManager::getInstance());
    EffectManager::getInstance()->setHolder(this);
    GameHolder* holder = new GameHolder();
    holder->nodeHolder = this->map;
    holder->worldHolder = this->world;
    ItemFactory::getInstance()->setHolder(holder);
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
    if(this->world != NULL){
        this->world->SetContactListener(listener);
    }
}

void GameWorld::update(float dt)
{
    this->map->update(dt);
    this->group1->update(dt);
    this->group2->update(dt);

    if(this->world != NULL)
    {
        world->Step(1/40.000f,8, 1);
    }
}


void GameWorld::draw()
{
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//    kmGLPushMatrix();
//    world->DrawDebugData();
//    kmGLPopMatrix();
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
    
    this->cameraFollowAction = CCFollow::create(group->getFollowingCharacter()->getSprite(),CCRect(0, 0, this->width, this->height));

    this->runAction(this->cameraFollowAction);
}

//PHYSICS CONTACT
void GameWorld::BeginContact(b2Contact *contact)
{
    this->group1->BeginContact(contact);
    this->group2->BeginContact(contact);
    GameObjectManager::getInstance()->BeginContact(contact);
}

void GameWorld::EndContact(b2Contact *contact)
{
    this->group1->EndContact(contact);
    this->group2->EndContact(contact);
    GameObjectManager::getInstance()->EndContact(contact);
}

void GameWorld::foo()
{
    this->group1->test();
}

Character* GameWorld::getCharacter()
{
    return this->group1->getCharacterOfPlayer();
}