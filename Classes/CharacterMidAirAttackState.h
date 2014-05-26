//
//  CharacterMidAirAttack.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterMidAirAttack__
#define __Headball__CharacterMidAirAttack__

class CharacterMidAirAttackState;

#include <iostream>
#include "CharacterState.h"

class CharacterMidAirAttackState: public CharacterState
{
private:
protected:
public:
    CharacterMidAirAttackState(Character* character);
    
    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();

};
#endif /* defined(__Headball__CharacterMidAirAttack__) */
