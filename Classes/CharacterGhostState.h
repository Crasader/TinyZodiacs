//
//  CharacterGhostState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterGhostState__
#define __Headball__CharacterGhostState__

#include <iostream>
#include "CharacterState.h"

class CharacterGhostState: public CharacterState
{
private:
protected:
public:
    CharacterGhostState(Character* character);

    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();

};
#endif /* defined(__Headball__CharacterGhostState__) */
