//
//  Hero.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__Hero__
#define __Headball__Hero__

class Hero;

#include <iostream>
#include "Character.h"
#include "cocos2d.h"
#include "Item.h"
#include "GameObjectManager.h"
#include "Controller.h"
#include "ControllerManager.h"

class Hero : public Character, public Controller
{
private:
protected:
   
    uint16  getCorrectGroup(Group group);
public:
    Hero();
    ~Hero();
    CC_SYNTHESIZE_RETAIN(CCAnimation*, ghostAnimation, GhostAnimation);
    
    virtual bool init();
    virtual void onCreate();
    
    virtual void update(float dt);
    
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    void pickUp(Item* item);
    virtual void attachSpriteTo(CCNode* node);
    virtual void destroy();
    
    bool receiveCommand(CommandID commandID, void* data);
    
    virtual void notifyUIChange(void* data);
    
    CREATE_FUNC(Hero);
};
#endif /* defined(__Headball__Hero__) */
