//
//  Hero.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__Hero__
#define __Headball__Hero__

#include <iostream>
#include "Character.h"
#include "cocos2d.h"
class Hero : public Character
{
private:
protected:
    Hero();
    ~Hero();
public:
    CC_SYNTHESIZE_RETAIN(CCAnimation*, skill2Animation, Skill2Animation);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, skill1Animation, Skill1Animation);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, ghostAnimation, GhostAnimation);
    
    virtual bool init();
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    
};
#endif /* defined(__Headball__Hero__) */
