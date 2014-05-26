//
//  CharacterDieState.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/25/14.
//
//

#ifndef __TinyZodiacs__CharacterDieState__
#define __TinyZodiacs__CharacterDieState__

class CharacterDieState;

#include <iostream>

#include "CharacterState.h"

class CharacterDieState: public CharacterState
{
private:
protected:
public:
    CharacterDieState(Character* character);
    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();
    
};
#endif /* defined(__TinyZodiacs__CharacterDieState__) */
