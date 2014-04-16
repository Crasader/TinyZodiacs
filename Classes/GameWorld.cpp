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
#include "CharacterFactory.h"
#include "GameObjectInfoView.h"
#include "InfoViewCreator.h"
#include "Util.h"

GameWorld::GameWorld()
{
    this->width = 0;
    this->height = 0;
    this->listInfoView = CCArray::create();
    this->listInfoView->retain();
    
    this->listCharacter = CCArray::create();
    this->listCharacter->retain();
    
}

GameWorld::~GameWorld()
{
    //CC_SAFE_RELEASE_NULL(this->map);
    //    this->world->ClearForces();
    //   delete this->world;
}

bool GameWorld::init()
{
    b2Vec2 gravity = b2Vec2(GRAVITY_ACCELERATION_X, GRAVITY_ACCELERATION_Y);
    this->world = new b2World(gravity);
    
    //DEBUG WORLD
    b2Draw* _debugDraw = new GLESDebugDraw(PTM_RATIO);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
 //   flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    //    flags += b2Draw::e_centerOfMassBit;
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
    //
    //CHARACTER
    this->character = ObjectFactory::getSharedManager()->createCharacter("map2", world, true);
    this->map->addChild(character->getSprite(), CHARACTER_LAYER);
    this->character->setPositionInPixel(ccp(400,800));
    this->setFollowCharacter(true);
    this->map->scheduleUpdate();
    
    //CHARACTER
    this->c1 = ObjectFactory::getSharedManager()->createCharacter("map2", world, false);
    this->map->addChild(c1->getSprite(), CHARACTER_LAYER);
    this->c1->setPositionInPixel(ccp(600,1000));
    
    //CHARACTER
    this->c2 = ObjectFactory::getSharedManager()->createCharacter("map2", world, false);
    this->map->addChild(c2->getSprite(), CHARACTER_LAYER);
    this->c2->setPositionInPixel(ccp(800,1200));
    
    this->character->setGroup(GROUP_HERO_A);

    this->c1->setGroup(GROUP_TERRAIN);
    this->c2->setGroup(GROUP_TERRAIN);
    
    CCObject* object1 = NULL;
    //
    for(int i=0;i<0;i++)
    {
        Character* hero = ObjectFactory::getSharedManager()->createCharacter("map2", world, false);
        hero->setPositionInPixel(ccp(20+30*i,400+20*i));
        
        hero->setGroup(GROUP_TERRAIN);
        this->listCharacter->addObject(hero);
        
    }
    CCSpriteBatchNode* batchnode = CCSpriteBatchNode::create("cat_spritesheet.png");
    CCARRAY_FOREACH(this->listCharacter, object1)
    {
        Character* hero = dynamic_cast<Character*>(object1);
        batchnode->addChild(hero->getSprite());
    }
    
    this->addChild(batchnode,100);
    

    //
    createWorldBox();
    //
    manager = PhysicBodyManager::getInstance();
    manager->setWorld(this->world);
    
    
    this->listInfoView->addObject(InfoViewCreator::createHeroInfoView(this->character, NULL));
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listInfoView, object)
    {
        GameObjectInfoView* gameObjectInfoView = dynamic_cast<GameObjectInfoView*>(object);
        this->addChild(gameObjectInfoView,100);
    }
    
    
    
    //Add manager
     addManager();
    return true;
}

void GameWorld::addManager()
{
    this->addChild(ScheduleManager::getInstance());
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
    
    //
    
}

void GameWorld::setContactListener(b2ContactListener *listener){
    if(this->world != NULL){
        this->world->SetContactListener(listener);
    }
}

void GameWorld::update(float dt)
{
    if(this->world != NULL)
    {
        manager->update(dt);
        world->Step(1/40.000f,8, 1);
    }
    //  
        this->map->update(dt);
        this->character->update(dt);
    
        // update infoview
        CCObject* object = NULL;
       CCARRAY_FOREACH(this->listInfoView, object)
        {
            GameObjectInfoView* gameObjectInfoView = dynamic_cast<GameObjectInfoView*>(object);
            gameObjectInfoView->update(dt);
        }
    
        this->c1->update(dt);
        this->c2->update(dt);
    
        CCObject* object1 = NULL;
   
        CCARRAY_FOREACH(this->listCharacter, object1)
        {
            Character* hero = dynamic_cast<Character*>(object1);
            hero->update(dt);
        }
    
}

void GameWorld::setFollowCharacter(bool follow)
{
    if(follow)
    {
        CCFollow *follow = CCFollow::create(this->character->getSprite(),CCRect(0, 0, this->width, this->height));
        this->runAction(follow);
    }
    else
    {
        this->stopAllActions();
    }
    
}

void GameWorld::draw()
{
        ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
        kmGLPushMatrix();
        world->DrawDebugData();
        kmGLPopMatrix();
}

//PHYSICS CONTACT
void GameWorld::BeginContact(b2Contact *contact)
{
    character->BeginContact(contact);
    this->c1->BeginContact(contact);
    this->c2->BeginContact(contact);
    
    CCObject* object1 = NULL;
    
    CCARRAY_FOREACH(this->listCharacter, object1)
    {
        Character* hero = dynamic_cast<Character*>(object1);
        hero->BeginContact(contact);
    }
    
}
void GameWorld::EndContact(b2Contact *contact)
{
    character->EndContact(contact);
    this->c1->EndContact(contact);
    this->c2->EndContact(contact);
    
    CCObject* object1 = NULL;
    
    CCARRAY_FOREACH(this->listCharacter, object1)
    {
        Character* hero = dynamic_cast<Character*>(object1);
        hero->BeginContact(contact);
    }
    
}

void GameWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    character->PreSolve(contact,oldManifold);

}
void GameWorld::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    character->PostSolve(contact,impulse);

}