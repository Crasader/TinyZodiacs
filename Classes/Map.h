//
//  Map.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#ifndef __SampleCocosProject__Map__
#define __SampleCocosProject__Map__

#include <iostream>
#include "cocos2d.h"
#include "MapObject.h"
#include "Box2D/Box2D.h"
#include "Character.h"
#include "HealthBar.h"
#include "SensorObject.h"
#include "Tower.h"
#include "TowerDTO.h"
#include "MonsterFactoryDTO.h"
#include "MapDTO.h"
#include "ItemCreator.h"

USING_NS_CC;

class Map: public cocos2d::CCNode
{
private:

    CCArray* listMapObject;
    CCArray* listSensorObject;
    CCArray* listItemCreator;
 
    HealthBar* bar;
    
protected:
public:
    CC_SYNTHESIZE(float, width, Width);
    CC_SYNTHESIZE(float, height, Height);
    CC_SYNTHESIZE(CCParallaxNode*, parallaxBackground, ParallaxBackground);
    CC_SYNTHESIZE(MapDTO*, mapDTO, MapDTO);
    
    Map();
    virtual ~Map();
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(Map);
    
    void addMapObject(MapObject* mapObject);
    void addSensorObject(SensorObject* sensorObject);
    void addItemCreator(ItemCreator* itemCreator);
   
    
    void attachAllMapObject();
    void addParallaxBackground(CCParallaxNode* parallaxBackground);
    void addParallaxForeground(CCParallaxNode* parallaxForeground);

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);

    
};

#endif /* defined(__SampleCocosProject__Map__) */
