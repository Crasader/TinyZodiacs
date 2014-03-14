//
//  CharacterSkill1State.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterSkill1State__
#define __Headball__CharacterSkill1State__

#include <iostream>
#include "CharacterState.h"

class CharacterSkillState: public CharacterState
{
private:
protected:
public:
    CharacterSkillState(Character* character);
    virtual void update(float dt);
    
    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();

};
#endif /* defined(__Headball__CharacterSkill1State__) */
