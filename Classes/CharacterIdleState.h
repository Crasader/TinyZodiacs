//
//  CharacterIdleState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterIdleState__
#define __Headball__CharacterIdleState__

#include <iostream>
#include "CharacterState.h"

class CharacterIdleState: public CharacterState
{
private:
protected:
public:
    CharacterIdleState(Character* character);

    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();

};
#endif /* defined(__Headball__CharacterIdleState__) */
