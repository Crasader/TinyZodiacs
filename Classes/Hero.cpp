//
//  Hero.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "Hero.h"

Hero::Hero()
{
    init();
}

bool Hero::init()
{
    if(!Character::init())
    {
        return false;
    }
    return true;
}

Hero::~Hero()
{
    if(this->skill1Animation != NULL)
    {
        this->skill1Animation->release();
    }
    if(this->skill2Animation != NULL)
    {
        this->skill2Animation->release();
    }
    if(this->ghostAnimation != NULL)
    {
        this->ghostAnimation->release();
    }
}

void Hero::BeginContact(b2Contact *contact)
{
    
}
void Hero::EndContact(b2Contact *contact)
{
    
}
