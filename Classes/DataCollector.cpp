//
//  DataCollector.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "DataCollector.h"

static DataCollector* instance = NULL;

DataCollector::DataCollector()
{
    this->dictAnimationObject = CCDictionary::create();
    this->dictAnimationObject->retain();
    this->dictMapDTO = CCDictionary::create();
    this->dictMapDTO->retain();
    this->dictHeroDTO = CCDictionary::create();
    this->dictHeroDTO->retain();
    this->dictMonsterDTO = CCDictionary::create();
    this->dictMonsterDTO->retain();
}

DataCollector::~DataCollector()
{
    
}

DataCollector* DataCollector::getInstance()
{
    if (instance == NULL) {
        instance = new DataCollector();
    }
    return instance;
}

//set
void DataCollector::setAnimationObject(const char* key, AnimationObject* object)
{
    this->dictAnimationObject->setObject(object, key);
}

void DataCollector::setMapDTO(const char* key, MapDTO* object)
{
    this->dictMapDTO->setObject(object, key);
}

void DataCollector::setHeroDTO(const char* key, HeroDTO* object)
{
    this->dictHeroDTO->setObject(object, key);
}

void DataCollector::setMonsterDTO(const char* key, HeroDTO* object)
{
    this->dictMonsterDTO->setObject(object, key);
}


//get
AnimationObject* DataCollector::getAnimationObjectByKey(const char *key)
{
    return (AnimationObject*)this->dictAnimationObject->objectForKey(key);
}

MapDTO* DataCollector::getMapDTOByKey(const char* key)
{
    return (MapDTO*)this->dictMapDTO->objectForKey(key);
}

HeroDTO* DataCollector::getHeroDTOByKey(const char* key)
{
    return (HeroDTO*)this->dictHeroDTO->objectForKey(key);
}

MonsterDTO* DataCollector::getMonsterDTOByKey(const char* key)
{
     return (MonsterDTO*)this->dictMonsterDTO->objectForKey(key);
}


