//
//  CharacterAttackState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterAttackState__
#define __Headball__CharacterAttackState__

class CharacterAttackState;

#include <iostream>
#include "CharacterState.h"
#include "NormalAttack.h"
#include "AbstractSkill.h"

USING_NS_CC;

class CharacterAttackState: public CharacterState
{
private:
    bool isfinishedAnimation;
    AbstractSkill* skill;
    AnimationObject* skillAnimation;
protected:
public:
    CharacterAttackState(Character* character, AbstractSkill* skill, AnimationObject* skillAnimation);
    
    virtual void update(float dt);

    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();
    
    void onFinishAttackAnimation();

};
#endif /* defined(__Headball__CharacterAttackState__) */
