//
//  CharacterSkill1State.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterSkillState.h"

CharacterSkillState::CharacterSkillState(Character* character): CharacterState(character)
{
   
}

bool CharacterSkillState::onEnterState()
{
     CCLOG("enter skill state");
    return false;
}

bool CharacterSkillState::onExitState()
{
    return false;
}

void CharacterSkillState::update(float dt)
{
    
}

bool CharacterSkillState::attack()
{
    return false;
}

bool CharacterSkillState::move()
{
    return false;
}

bool CharacterSkillState::jump()
{
    return false;
}

bool CharacterSkillState::useSkill()
{
    return false;
}