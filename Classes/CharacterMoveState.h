//
//  CharacterMoveState.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/8/14.
//
//

#ifndef __SampleCocosProject__CharacterMoveState__
#define __SampleCocosProject__CharacterMoveState__

#include <iostream>
#include "CharacterState.h"
#include "Character.h"

class CharacterMoveState: public CharacterState
{
    
private:
       
protected:
public:
    CharacterMoveState(Character* character);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual void update(float dt);
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();
};

#endif /* defined(__SampleCocosProject__CharacterMoveState__) */
