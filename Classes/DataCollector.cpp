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
    this->dictItemDTO = CCDictionary::create();
    this->dictItemDTO->retain();
    this->dictTowerDTO = CCDictionary::create();
    this->dictTowerDTO->retain();
    this->dictResourcePack = CCDictionary::create();
    this->dictResourcePack->retain();
    
    matchData.mapIDSelected = "";
    matchData.heroIDSelected = "";

}

DataCollector::~DataCollector()
{
    this->dictAnimationObject->release();
    this->dictMapDTO->release();
    this->dictHeroDTO->release();
    this->dictMonsterDTO->release();
    this->dictItemDTO->release();
    this->dictTowerDTO->release();
    this->dictResourcePack->release();
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
    if(this->dictAnimationObject->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictAnimationObject->setObject(object, key);
}

void DataCollector::setMapDTO(const char* key, MapDTO* object)
{
    if(this->dictMapDTO->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictMapDTO->setObject(object, key);
}

void DataCollector::setHeroDTO(const char* key, HeroDTO* object)
{
    if(this->dictHeroDTO->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictHeroDTO->setObject(object, key);
}

void DataCollector::setMonsterDTO(const char* key, MonsterDTO* object)
{
    if(this->dictMonsterDTO->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictMonsterDTO->setObject(object, key);
}

void DataCollector::setItemDTO(const char* key, ItemDTO* object)
{
    if(this->dictItemDTO->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictItemDTO->setObject(object, key);

}

void DataCollector::setTowerDTO(const char* key, TowerDTO* object)
{
    if(this->dictTowerDTO->objectForKey(key) != NULL)
    {
        return;
    }
    this->dictTowerDTO->setObject(object, key);
}

void DataCollector::setResourcePack(const char* key, ResourcePack* object)
{
    if(this->dictResourcePack->objectForKey(key) != NULL)
    {
        return;
    }
     this->dictResourcePack->setObject(object, key);
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

ItemDTO* DataCollector::getItemDTOByKey(const char* key)
{
    return (ItemDTO*)this->dictItemDTO->objectForKey(key);
}

TowerDTO* DataCollector::getTowerDTOByKey(const char* key)
{
    return (TowerDTO*)this->dictTowerDTO->objectForKey(key);
}

ResourcePack* DataCollector::getResourcePackByKey(const char* key)
{
    return (ResourcePack*)this->dictResourcePack->objectForKey(key);
}

MatchData* DataCollector::getMatchData()
{
    return &matchData;
}

