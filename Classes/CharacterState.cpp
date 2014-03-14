//
//  CharacterState.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/5/14.
//
//

#include "CharacterState.h"
#include "Character.h"

CharacterState::CharacterState()
{

}

CharacterState::CharacterState(Character* character)
{
    this->character = character;
}

CharacterState::~CharacterState()
{
    this->character = NULL;
}