//
//  CharacterAttackState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterAttackState__
#define __Headball__CharacterAttackState__

#include <iostream>
#include "CharacterState.h"
#include "NormalAttack.h"

USING_NS_CC;

class CharacterAttackState: public CharacterState
{
private:
protected:
public:
    CharacterAttackState(Character* character);
    
    virtual void update(float dt);

    virtual bool onEnterState();
    virtual bool onExitState();
    
    virtual bool attack();
    virtual bool jump();
    virtual bool useSkill();
    virtual bool move();
    
    void onFinishAttackAnimation(cocos2d::CCObject* pSender, void* object);

};
#endif /* defined(__Headball__CharacterAttackState__) */
