//
//  CharacterActionEngine.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#include "CharacterActionEngine.h"
CharacterActionEngine::CharacterActionEngine(Character* character)
{
    this->character = character;
}
CharacterActionEngine::~CharacterActionEngine()
{
    
}

void CharacterActionEngine::moveLeft()
{
    if(this->character != NULL)
    {
        this->character->move(LEFT);
    }
}
void CharacterActionEngine::moveRight()
{
    if(this->character != NULL)
    {
        this->character->move(RIGHT);
    }
}
void CharacterActionEngine::jump()
{
    if(this->character != NULL)
    {
        this->character->jump();
    }
}
void CharacterActionEngine::fallDown()
{
    if(this->character != NULL)
    {
    }
}
void CharacterActionEngine::attack()
{
    if(this->character != NULL)
    {
        this->character->attack();
    }
}
void CharacterActionEngine::skill1()
{
    if(this->character != NULL)
    {
        this->character->useSkill1();
    }
}
void CharacterActionEngine::skill2()
{
    if(this->character != NULL)
    {
        this->character->useSkill2();
    }
}