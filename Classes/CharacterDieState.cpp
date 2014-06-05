//
//  CharacterDieState.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/25/14.
//
//

#include "CharacterIdleState.h"
#include "CharacterMoveState.h"
#include "CharacterMidAirState.h"
#include "CharacterAttackState.h"
#include "CharacterJumpState.h"
#include "CharacterDieState.h"

CharacterDieState::CharacterDieState(Character* character): CharacterState(character)
{
    
}

bool CharacterDieState::onEnterState()
{
    CCArray* arr = CCArray::create();
    
    if(this->character->dieAnimation != NULL)
    {
        CCAnimate* dieAnimate = CCAnimate::create(this->character->dieAnimation->getAnimation());
        arr->addObject(dieAnimate);
    }
    
    CCCallFunc* dieFunction = CCCallFunc::create(this, callfunc_selector(CharacterDieState::die));
    arr->addObject(dieFunction);
    
    action = CCSequence::create(arr);
    action->retain();
    this->character->getSprite()->runAction(action);
    return true;
}

bool CharacterDieState::onExitState()
{
    this->stopAction();
    return true;
}

void CharacterDieState::update(float dt)
{
}

bool CharacterDieState::attack()
{
    return false;
}

bool CharacterDieState::move()
{
    return false;
}

bool CharacterDieState::jump()
{
    return false ;
}

bool CharacterDieState::useSkill()
{
    return false;
}

void CharacterDieState::die()
{
    this->character->destroy();
}
