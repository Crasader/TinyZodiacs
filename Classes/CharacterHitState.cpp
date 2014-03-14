//
//  CharacterHitState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterHitState.h"

CharacterHitState::CharacterHitState(Character* character): CharacterState(character)
{
    
}

bool CharacterHitState::onEnterState()
{
    return false;
}

bool CharacterHitState::onExitState()
{
    return false;
}

void CharacterHitState::update(float dt)
{
    
}

bool CharacterHitState::attack()
{
    return false;
}

bool CharacterHitState::move()
{
    return false;
}

bool CharacterHitState::jump()
{
    return false;
}

bool CharacterHitState::useSkill()
{
    return false;
}