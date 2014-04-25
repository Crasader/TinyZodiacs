//
//  CharacterState.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/5/14.
//
//

#ifndef __SampleCocosProject__CharacterState__
#define __SampleCocosProject__CharacterState__

#include <iostream>
#include "CharacterState.h"
#include "Character.h"
#include "ObjectState.h"

class CharacterState: public ObjectState
{
private:
    
protected:
    Character* character;
public:
    CharacterState();
    CharacterState(Character* character);
    virtual ~CharacterState();
    
    virtual void update(float dt) = 0;

    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack() = 0;
    virtual bool jump() = 0;
    virtual bool useSkill() = 0;
    virtual bool move() = 0;
};

#endif /* defined(__SampleCocosProject__CharacterState__) */
