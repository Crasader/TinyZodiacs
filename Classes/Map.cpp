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
    this->listSensorObject = CCArray::create();
    this->listSensorObject->retain();
    this->listTowerDTO = CCArray::create();
    this->listTowerDTO->retain();
    this->listMonsterFactoryDTO = CCArray::create();
    this->listMonsterFactoryDTO->retain();
}

Map::~Map()
{
    CC_SAFE_RELEASE_NULL(listMapObject);
    CC_SAFE_RELEASE_NULL(listSensorObject);
    CC_SAFE_RELEASE_NULL(listTowerDTO);
    CC_SAFE_RELEASE_NULL(listMonsterFactoryDTO);
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

void Map::addTowerDTO(TowerDTO* towerDTO)
{
    if(towerDTO != NULL)
    {
        this->listTowerDTO->addObject(towerDTO);
    }
}

void Map::addMonsterFactoryDTO(MonsterFactoryDTO* monsterFactoryDTO)
{
    if(monsterFactoryDTO != NULL)
    {
        this->listMonsterFactoryDTO->addObject(monsterFactoryDTO);
    }
}


void Map::attachAllMapObject()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(listMapObject,object)
    {
        MapObject* mapObject = (MapObject*)object;
          //mapObject->getSprite()->setVisible(false);
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

void  Map::BeginContact(b2Contact *contact)
{
    if(this->listMapObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listMapObject,object)
        {
            MapObject* mapObject = (MapObject*)object;
            mapObject->BeginContact(contact);
        }
    }
    if(this->listSensorObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listSensorObject,object)
        {
            SensorObject* sensorObject = (SensorObject*)object;
            sensorObject->BeginContact(contact);
        }
    }
}

void  Map::EndContact(b2Contact *contact)
{
    if(this->listMapObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listMapObject,object)
        {
            MapObject* mapObject = (MapObject*)object;
            mapObject->EndContact(contact);
        }
    }
    if(this->listSensorObject != NULL)
    {
        CCObject* object = NULL;
        
        CCARRAY_FOREACH(listSensorObject,object)
        {
            SensorObject* sensorObject = (SensorObject*)object;
            sensorObject->EndContact(contact);
        }
    }
}
