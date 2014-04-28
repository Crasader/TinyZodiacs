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

USING_NS_CC;

class Monster: public Character
{
private:
    CC_SYNTHESIZE(int, laneID, LaneID);
    CC_SYNTHESIZE_READONLY(b2Body*, sensor, Sensor);
protected:
    void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
public:
    bool isStopMove;
    Monster();
    ~Monster();
    
    virtual bool init();
    virtual void update(float dt);
    
    void doAction(SensorObject* sensorObject);

    void notifyByEffect(CCObject* effect);
    
    CREATE_FUNC(Monster);
    
};

#endif /* defined(__Headball__Monster__) */
