//
//  Monster.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "Monster.h"

Monster::Monster()
{
    
}

Monster::~Monster()
{
    
}

bool Monster::init()
{
    if (!Character::init()) {
        return false;
    }
    this->sprite = CCSprite::create();
    return true;
}