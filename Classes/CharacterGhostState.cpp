//
//  CharacterGhostState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterGhostState.h"

CharacterGhostState::CharacterGhostState(Character* character): CharacterState(character)
{
    
}

bool CharacterGhostState::onEnterState()
{
    return false;
}

bool CharacterGhostState::onExitState()
{
    return false;
}

void CharacterGhostState::update(float dt)
{
    
}

bool CharacterGhostState::attack()
{
    return false;
}

bool CharacterGhostState::move()
{
    return false;
}

bool CharacterGhostState::jump()
{
    return false;
}

bool CharacterGhostState::useSkill()
{
    return false;
}