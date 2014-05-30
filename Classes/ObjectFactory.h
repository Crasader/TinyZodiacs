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
#include "DataCollector.h"
#include "ContainerItem.h"
#include "Constants.h"
#include "Util.h"
#include "GoldItem.h"
#include "BonusItem.h"
#include "EffectFactory.h"
#include "ItemCreator.h"
#include "ItemCreatorDTO.h"
#include "MainCrystal.h"

#define TAG_BODY "body"
#define TAG_ANIMATION "animation"
#define TAG_HP "hp"
#define TAG_ATTACK "atk"
#define TAG_DEFENSE "def"
#define TAG_SPEED "speed"
#define TAG_ATTACK_SPEED "atk_speed"
#define TAG_MAX_JUMP "max_jump"
#define TAG_JUMP_HEIGHT "jump_height"
#define TAG_SKILL_0 "skill_0"
#define TAG_SKILL_1 "skill_1"
#define TAG_SKILL_2 "skill_2"


#define RUN "-run"
#define ATTACK "-attack"
#define JUMP "-jump"
#define IDLE "-idle"
#define FALL "-fall"
#define FLY "-fly"
#define SKILL "-skill"

//ITEM ANIMATION

#define item_prepareToAppear "-prepareToAppear"
#define item_appear "-appear"
#define item_prepareToDisappear "-prepareToDisappear"



class Item;
class ObjectFactory
{
public:
    static Hero* createHero(HeroDTO* heroDTO, b2World* world, bool isLocal);
    static MapObject* createMapObject(const char *idMapObject, b2World *world);
    static MapObject* createMapObject(MapObjectDTO* mapObjectDTO, b2World *world);
    static SensorObject* createSensorObject(b2Vec2 dumb, b2World *world, CCPoint position);
    static SensorObject* createSensorObject(SensorObjectDTO* sensorObjectDTO, b2World* world);
    static Tower* createTower(TowerStructDTO* towerStructDTO, b2World* world);
    
    static Item* createItem(ItemDTO* itemDTO, b2World* world);
    static Item* createContainerItem(ItemDTO* itemDTO, b2World* world);
    static Item* createGoldItem(ItemDTO* itemDTO, b2World* world);
    static Item* createBonusItem(ItemDTO* itemDTO, b2World* world);
    static ItemCreator* createItemCreator(ItemCreatorDTO* itemCreatorDTO);
    
    
};

#endif /* defined(__SampleCocosProject__ObjectFactory__) */
