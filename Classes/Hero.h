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
    
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
    void pickUp(Item* item);
    
    CREATE_FUNC(Hero);
};
#endif /* defined(__Headball__Hero__) */
