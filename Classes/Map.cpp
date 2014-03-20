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
#include "GameBackgroundLayer.h"
#include "LayerIndexConstants.h"

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
    CC_SAFE_RELEASE_NULL(listMapObject);
}

bool Map::init()
{
    if(!CCNode::create())
    {
        return false;
    }
    return true;
}

void Map::update(float dt)
{
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

void Map::addMapObject(MapObject *mapObject)
{
    if(mapObject != NULL)
    {
        this->listMapObject->addObject(mapObject);
    }
}


void Map::attachAllMapObject()
{
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("map2_spritesheet.png");
    CCObject* object;
    CCARRAY_FOREACH(listMapObject,object)
    {
        MapObject* mapObject = (MapObject*)object;
      //  mapObject->getSprite()->setPosition(ccp(2000,2000));
       batchNode->addChild(mapObject->getSprite());
        
    }
    
    this->addChild(batchNode,MAPOBJECT_LAYER);
}

void Map::addParallaxBackground(CCParallaxNode* parallaxBackground)
{
    this->addChild(parallaxBackground, BACKGROUND_LAYER);
}
