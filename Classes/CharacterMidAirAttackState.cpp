//
//  CharacterMidAirAttack.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterMidAirAttackState.h"

CharacterMidAirAttackState::CharacterMidAirAttackState(Character* character): CharacterState(character)
{
    
}

bool CharacterMidAirAttackState::onEnterState()
{
    return false;
}

bool CharacterMidAirAttackState::onExitState()
{
    this->character->getSprite()->stopAllActions();
    return true;
}

void CharacterMidAirAttackState::update(float dt)
{
    
}

bool CharacterMidAirAttackState::attack()
{
    return false;
}

bool CharacterMidAirAttackState::move()
{
    return false;
}

bool CharacterMidAirAttackState::jump()
{
    return false;
}

bool CharacterMidAirAttackState::useSkill()
{
    return false;
}