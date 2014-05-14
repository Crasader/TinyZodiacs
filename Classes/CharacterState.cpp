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
    this->action = NULL;
}

CharacterState::~CharacterState()
{
    this->character = NULL;
}

void CharacterState::stopAction()
{
    if(this->action != NULL && this->character != NULL)
    {
        if(this->action->isDone() == false)
        {
            this->character->getSprite()->stopAction(this->action);
            this->action->release();
        }
    }
}

bool CharacterState::init()
{
    return true;
}