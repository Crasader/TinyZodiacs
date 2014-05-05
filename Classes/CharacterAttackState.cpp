//
//  CharacterAttackState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterAttackState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"


CharacterAttackState::CharacterAttackState(Character* character, AbstractSkill* skill, AnimationObject* skillAnimation): CharacterState(character)
{
    this->skillAnimation = skillAnimation;
    this->skill = skill;
}

bool CharacterAttackState::onEnterState()
{
  //  CCLOG("enter attack state");
    CCAnimate* animation = CCAnimate::create(this->skillAnimation->getAnimation());
    CCCallFunc* callBack = CCCallFunc::create(this, callfunc_selector(CharacterAttackState::onFinishAttackAnimation));
    
    CCArray* arr = CCArray::create();
    arr->addObject(animation);
    arr->addObject(callBack);
    
    this->action = CCSequence::create(arr);
    this->character->getSprite()->runAction( this->action);
//
    //Excute attack
    this->skill->excute();
    return true;
}

bool CharacterAttackState::onExitState()
{
    stopAction();
    //stop attack
    this->skill->stop();
    return true;
}

void CharacterAttackState::update(float dt)
{
    
}

bool CharacterAttackState::attack()
{
    return true;
}

bool CharacterAttackState::move()
{
    return true;
}

bool CharacterAttackState::jump()
{
    return true;
}

bool CharacterAttackState::useSkill()
{
    return false;
}

void CharacterAttackState::onFinishAttackAnimation()
{
    this->character->changeState(new CharacterIdleState(this->character));
}