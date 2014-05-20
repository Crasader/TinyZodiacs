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

class Hero : public Character
{
private:
protected:
    Hero();
    ~Hero();
    
    uint16  getCorrectGroup(Group group);
public:
    CC_SYNTHESIZE_RETAIN(CCAnimation*, ghostAnimation, GhostAnimation);
    
    virtual bool init();
    virtual void onCreate();
    
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    void pickUp(Item* item);
    virtual void attachSpriteTo(CCNode* node);
    
    CREATE_FUNC(Hero);
};
#endif /* defined(__Headball__Hero__) */
