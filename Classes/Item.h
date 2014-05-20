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

USING_NS_CC;
class Item: public GameObject {
private:
    CC_SYNTHESIZE(bool, isActive, IsActive);
    CC_SYNTHESIZE(float, lifeTime, LifeTime);

    CCAction* lifeTimeAction;
protected:
    CC_SYNTHESIZE(AnimationObject*, prepareToDisappearAnimation, prepareToDisappearAnimation);
    CC_SYNTHESIZE(AnimationObject*, prepareToAppearAnimation, PrepareToAppearAnimation);
    CC_SYNTHESIZE(AnimationObject*, appearAnimation, AppearAnimation);

public:
    int id;
    Item();
    virtual ~Item();
    
    virtual bool init();
    virtual void onCreate();
    virtual void destroy();
    virtual void startSchedule();

    virtual void prepareToAppear();
    virtual void appear();
    virtual void prepareToDisappearInTimeOut();
    virtual void prepareToDisappearInContact(GameObject* contactGameObject);
      virtual void prepareToDisappearInOpen();
    virtual void disappear();

    virtual void contact(GameObject* contactGameObject);
    virtual void open(GameObject* openGameObject);
    
    void attachSpriteTo(CCNode* node);
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
    
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notifyToDestroy();
    
    CREATE_FUNC(Item);
};

#endif /* defined(__TinyZodiacs__Item__) */