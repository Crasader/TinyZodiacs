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

GameWorld::GameWorld(float bottom, float left, float width, float height)
{
    this->bottom = bottom;
    this->left = left;
    this->width = width;
    this->height = height;
    init();
}

bool GameWorld::init()
{
    b2Vec2 gravity = b2Vec2(GRAVITY_ACCELERATION_X, GRAVITY_ACCELERATION_Y);
    this->world = new b2World(gravity);
    
    //DEBUG WORLD
    b2Draw* _debugDraw = new GLESDebugDraw(PTM_RATIO);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
    //    flags += b2Draw::e_pairBit;
    //    flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
    this->world->SetDebugDraw(_debugDraw);
    //
    createWorldBox();
    
    //Set contact listener
    this->setContactListener(this);
    
    //MAP
    MapCreator* mapCreator = new MapCreator();
    
    map = mapCreator->createMap("dsdsd",this);
    map->attachAllMapObject();
    
    this->addChild(map,1);
    
    delete mapCreator;
    
    
    this->scheduleUpdate();
    //  map->addChild(backgroundLayer,0);
    
    //CHARACTER
    this->character = ObjectFactory::getSharedManager()->createCharacter("��dasdsad", world);
    this->addChild(character->getSprite(),2);
    this->character->setPositionInPixel(ccp(400,400));
    this->setFollowCharacter(true);
    
    this->character->setNormalAttack(new NormalAttack(this->character));
    //this->map->scheduleUpdate();

    
    return true;
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
    rightEdgeShape.Set(b2Vec2(0, 0), b2Vec2(0/PTM_RATIO,this->height/PTM_RATIO));
    this->rightLine->CreateFixture(&rightFixtureDef);
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
        world->Step(1/60.000f,8, 3);
    }
    
   // this->map->update(dt);
    this->character->update(dt);
    
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

void GameWorld::BeginContact(b2Contact *contact)
{
    character->BeginContact(contact);
}
void GameWorld::EndContact(b2Contact *contact)
{
    character->EndContact(contact);
}