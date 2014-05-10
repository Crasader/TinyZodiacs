//
//  Monster.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__Monster__
#define __Headball__Monster__

#include <iostream>
#include "cocos2d.h"
#include "Character.h"
#include "SensorObject.h"
#include "Constants.h"
#include "ItemFactory.h"

USING_NS_CC;

class Monster: public Character
{
private:    
    CC_SYNTHESIZE(int, laneID, LaneID);
    CC_SYNTHESIZE_READONLY(b2Body*, sensor, Sensor);
    CCArray* listTarget;
    Direction defaultDirection;
    CC_SYNTHESIZE(vector<ItemStruct>, listItem, listItem);
protected:
    void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
    
    virtual void setPhysicGroup(uint16 group);
    void setSensorGroup(uint16 group);
    virtual uint16 getCorrectGroup(Group group);
    virtual void aimTarget();
public:
    bool isStopMove;
    bool isAttack;
    Monster();
    ~Monster();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void setGroup(Group group);
    
    void setSensor(b2Body* sensor);
    
    void doAction(SensorObject* sensorObject);

    void notifyByEffect(CCObject* effect);
    
    CREATE_FUNC(Monster);
    
};

#endif /* defined(__Headball__Monster__) */
