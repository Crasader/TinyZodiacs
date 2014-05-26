//
//  CharacterHitState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterHitState__
#define __Headball__CharacterHitState__

class CharacterHitState;

#include <iostream>
#include "CharacterState.h"

class CharacterHitState: public CharacterState
{
private:
protected:
public:
    CharacterHitState(Character* character);

    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();

};
#endif /* defined(__Headball__CharacterHitState__) */
