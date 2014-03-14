//
//  CharacterMidAirState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterMidAirState__
#define __Headball__CharacterMidAirState__

#include <iostream>
#include "CharacterState.h"

class CharacterMidAirState: public CharacterState
{
private:
    bool isFlying;
    bool isFalling;
protected:
public:
    CharacterMidAirState(Character* character);
    
    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();
};
#endif /* defined(__Headball__CharacterMidAirState__) */
