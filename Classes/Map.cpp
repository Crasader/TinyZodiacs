//
//  Map.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 2/18/14.
//
//

#include "Map.h"
#include "MapObject.h"
#include "GLES-Render.h"
#include "ObjectFactory.h"

USING_NS_CC;

Map::Map()
{
    width = 0;
    height = 0;
    
    this->listMapObject = CCArray::create();
    this->listMapObject->retain();
    
}

Map::~Map()
{
    CC_SAFE_DELETE(listMapObject);
}

bool Map::init()
{
    if(!CCNode::create())
    {
        return false;
    }
    //SIZE MAP
    this->width = 2000;
    this->height = 1000;
    
    // WORLD
    b2Vec2 gravity;
    gravity.Set(0.0f,-10.0f);
    world = new b2World(gravity);
    
    //DEBUG WORLD
    b2Draw* _debugDraw = new GLESDebugDraw(32);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //    flags += b2Draw::e_jointBit;
    //    flags += b2Draw::e_aabbBit;
    //    flags += b2Draw::e_pairBit;
    //    flags += b2Draw::e_centerOfMassBit;
    _debugDraw->SetFlags(flags);
    this->world->SetDebugDraw(_debugDraw);
    
    
    //GROUND
    b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
    
	b2Body *groundBody = this->world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
    boxShapeDef.friction=0;
    
	//wall definitions
	groundEdge.Set(b2Vec2(0,0), b2Vec2(3000/32, 0));
	groundBody->CreateFixture(&boxShapeDef);
    
    
    //CHARACTER
    this->character = ObjectFactory::getSharedManager()->createCharacter("��dasdsad", world);
    this->addChild(character->getSprite(),2);
    this->character->setPositionInPixel(ccp(400,400));

    
    
    // character2->run();
    
    return true;
}

void Map::update(float dt)
{
    if(this->world != NULL)
    {
        world->Step(1/40.000f,8, 3);
        
        if(listMapObject != NULL)
        {
            CCObject* object;
            
            CCARRAY_FOREACH(listMapObject,object)
            {
                MapObject* mapObject = (MapObject*)object;
                mapObject->update(dt);
                
            }
        }
        
    }
    
    character->update(dt);
}

void Map::draw()
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    world->DrawDebugData();
    kmGLPopMatrix();
}

void Map::addMapObject(MapObject *mapObject)
{
    if(mapObject!=NULL)
    {
        this->listMapObject->addObject(mapObject);
    }
}

void Map::setFollowCharacter(bool follow)
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
b2World* Map::getWorld()
{
    return this->world;
}

Character* Map::getCharacter()
{
    return this->character;
}

void Map::attachAllMapObject()
{
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("map_spritesheet.png");
    CCObject* object;
    CCARRAY_FOREACH(listMapObject,object)
    {
        MapObject* mapObject = (MapObject*)object;
        mapObject->getSprite()->setPosition(ccp(2000,2000));
        batchNode->addChild(mapObject->getSprite());
        
    }
    
    this->addChild(batchNode,1);
}
