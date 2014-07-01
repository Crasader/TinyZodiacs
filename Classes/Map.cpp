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
#include "GameBackgroundLayer.h"
#include "LayerIndexConstants.h"

USING_NS_CC;

Map::Map()
{
    width = 0;
    height = 0;
    this->mapDTO = NULL;
    this->listMapObject = CCArray::create();
    this->listMapObject->retain();
    this->listSensorObject = CCArray::create();
    this->listSensorObject->retain();
    this->listItemCreator = CCArray::create();
    this->listItemCreator->retain();
    this->listWave = CCArray::create();
    this->listWave->retain();
    this->listWall = CCArray::create();
    this->listWall->retain();
    
    
}

Map::~Map()
{
    CC_SAFE_RELEASE_NULL(listMapObject);
    CC_SAFE_RELEASE_NULL(listSensorObject);
    CC_SAFE_RELEASE_NULL(listItemCreator);
    CC_SAFE_RELEASE_NULL(listWave);
    CC_SAFE_RELEASE_NULL(listWall);
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
    if(this->listMapObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listMapObject,object)
        {
            MapObject* mapObject = (MapObject*)object;
            mapObject->update(dt);
        }
    }
    if(this->listSensorObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listSensorObject,object)
        {
            SensorObject* sensorObject = (SensorObject*)object;
            sensorObject->update(dt);
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

void Map::addSensorObject(SensorObject* sensorObject)
{
    if(sensorObject != NULL)
    {
        this->listSensorObject->addObject(sensorObject);
    }
}

void Map::addWall(Wall* wall)
{
    if(wall != NULL)
    {
        this->listWall->addObject(wall);
    }
}

void Map::addItemCreator(ItemCreator* itemCreator)
{
    if(itemCreator != NULL)
    {
     //   itemCreator->start();
        this->listItemCreator->addObject(itemCreator);
    }
    
}

void Map::addWave(Wave* wave)
{
    if(wave != NULL)
    {
        this->listWave->addObject(wave);
    }
}

void Map::attachAllMapObject()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(listMapObject,object)
    {
        MapObject* mapObject = (MapObject*)object;
       // mapObject->getSprite()->setVisible(false);
        this->addChild(mapObject->getSprite(),MAPOBJECT_LAYER);
    }
}

void Map::addParallaxBackground(CCParallaxNode* parallaxBackground)
{
    this->addChild(parallaxBackground, BACKGROUND_LAYER);
}

void Map::addParallaxForeground(CCParallaxNode* parallaxForeground)
{
    this->addChild(parallaxForeground,FOREGROUND_LAYER );
}