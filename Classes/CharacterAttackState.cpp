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


CharacterAttackState::CharacterAttackState(Character* character): CharacterState(character)
{
    
} 

bool CharacterAttackState::onEnterState()
{
    
    CCAction* jumpAction = CCAnimate::create(this->character->attackAnimation->getAnimation());
    CCCallFuncND* callBack = CCCallFuncND::create(NULL, callfuncND_selector(CharacterAttackState::onFinishAttackAnimation), this->character);
    
    
    CCArray* arr = CCArray::create();
    arr->addObject(jumpAction);
    arr->addObject(callBack);
    
    CCSequence* sequence = CCSequence::create(arr);
    
    this->character->setAnchorPointForAnimation(this->character->attackAnimation->getOrigin());
    this->character->getSprite()->runAction(sequence);
    return true;
}

bool CharacterAttackState::onExitState()
{
    this->character->getSprite()->stopAllActions();
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
    this->character->changeState(new CharacterJumpState(this->character));
    return true;
}

bool CharacterAttackState::useSkill()
{
    return false;
}

void CharacterAttackState::onFinishAttackAnimation(cocos2d::CCObject* pSender, void* object)
{
    Character* character = (Character*)object;
    character->changeState(new CharacterIdleState(character));
}