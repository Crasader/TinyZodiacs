//
//  CharacterJumpState.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/7/14.
//
//

#ifndef __SampleCocosProject__CharacterJumpState__
#define __SampleCocosProject__CharacterJumpState__

#include <iostream>
#include "CharacterState.h"


class CharacterJumpState: public CharacterState
{
    
private:
    void finishJumpAction();
    
protected:
public:
    CharacterJumpState(Character* character);
  
    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
   
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();


};
#endif /* defined(__SampleCocosProject__CharacterJumpState__) */
