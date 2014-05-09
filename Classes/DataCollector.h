//
//  DataCollector.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__DataCollector__
#define __TinyZodiacs__DataCollector__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"
#include "Map.h"
#include "MapDTO.h"
#include "HeroDTO.h"
#include "MonsterDTO.h"
#include "ItemDTO.h"

USING_NS_CC;

class DataCollector
{
private:
    DataCollector();
    ~DataCollector();
    
    //Animation Dictionary
    CCDictionary* dictAnimationObject;
    //Map Dictionary
    CCDictionary* dictMapDTO;
    //Hero Dictionary
    CCDictionary* dictHeroDTO;
    //Monster Dictionary
    CCDictionary* dictMonsterDTO;
    //Item Dictionary
    CCDictionary* dictItemDTO;
    
    
protected:
public:
    static DataCollector* getInstance();
    
    //set
    void setAnimationObject(const char* key, AnimationObject* object);
    void setMapDTO(const char* key, MapDTO* object);
    void setHeroDTO(const char* key, HeroDTO* object);
    void setMonsterDTO(const char* key, MonsterDTO* object);
    void setItemDTO(const char* key, ItemDTO* object);
    
    //get
    AnimationObject* getAnimationObjectByKey(const char* key);
    MapDTO* getMapDTOByKey(const char* key);
    HeroDTO* getHeroDTOByKey(const char* key);
    MonsterDTO* getMonsterDTOByKey(const char* key);
    ItemDTO* getItemDTOByKey(const char* key);
    
};

#endif /* defined(__TinyZodiacs__DataCollector__) */
