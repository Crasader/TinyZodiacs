//
//  Item.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__Item__
#define __TinyZodiacs__Item__

class Item;

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"
#include "ScheduleManager.h"
#include "ItemFactory.h"
#include "Effect.h"

USING_NS_CC;

class Item: public GameObject {
private:
    CC_SYNTHESIZE(bool, canBePickedUp, CanBePickedUp);
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CC_SYNTHESIZE(CCArray*, listAffect, ListAffect);

    CCAction* lifeTimeAction;
protected:
public:
    Item();
    ~Item();
    
    virtual bool init();
    virtual void onCreate();
    void destroy();
    void prepareToDestroy();
    void startSchedule();
    void readyToBePickedUp();
    void prepareToPickedUpAndDestroy(CCNode* node);
    
    
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    
    
    CREATE_FUNC(Item);
};

#endif /* defined(__TinyZodiacs__Item__) */