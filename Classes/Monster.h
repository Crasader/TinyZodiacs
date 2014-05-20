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
//    CC_SYNTHESIZE_READONLY(b2Body*, sensor, Sensor);
    CCArray* listTarget;
    Direction defaultDirection;
    CC_SYNTHESIZE(vector<ItemStruct>, listItem, listItem);
protected:
  
    
    virtual void setPhysicGroup(uint16 group);
    void setSensorGroup(uint16 group);
    virtual uint16 getCorrectGroup(Group group);
    virtual void aimTarget();
public:
    void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    
    bool isStopMove;
    bool isAttack;
    Monster();
    ~Monster();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void setGroup(Group group);
    virtual void onCreate();
    virtual void destroy();
    virtual void attachSpriteTo(CCNode* node);
    void setSensor(b2Body* sensor);
    void setSensor(const char* bodyId);
    
    void doAction(SensorObject* sensorObject);

    void notifyByEffect(CCObject* effect);
    
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notifyToDestroy();
    
    CREATE_FUNC(Monster);
};

#endif /* defined(__Headball__Monster__) */
