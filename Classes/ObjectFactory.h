//
//  ObjectFactory.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__ObjectFactory__
#define __SampleCocosProject__ObjectFactory__

#include <iostream>
#include "Character.h"
#include "MapObject.h"
#include "MapObjectDTO.h"
#include "NoBodyMapObject.h"
#include "SensorObject.h"
#include "SensorObjectDTO.h"
#include "Tower.h"
#include "TowerDTO.h"
#include "Hero.h"
#include "HeroDTO.h"
#include "Item.h"
#include "ItemDTO.h"

class Item;
class ObjectFactory
{
public:
    ObjectFactory();
    ~ObjectFactory();

    static ObjectFactory* getSharedManager();
    Hero* createHero(HeroDTO* heroDTO, b2World* world, bool isLocal);
    Character* createCharacter(const std::string &name, b2World *world, bool isLocal);
    MapObject* createMapObject(const char *idMapObject, b2World *world);
    MapObject* createMapObject(MapObjectDTO* mapObjectDTO, b2World *world);
    SensorObject* createSensorObject(b2Vec2 dumb, b2World *world, CCPoint position);
    SensorObject* createSensorObject(SensorObjectDTO* sensorObjectDTO, b2World* world);
    Tower* createTower(TowerDTO* towerDTO, b2World* world);
    Item* createItem(ItemDTO* towerDTO, b2World* world);
};

#endif /* defined(__SampleCocosProject__ObjectFactory__) */
