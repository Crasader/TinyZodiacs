//
//  GameEffect.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#include "GameEffect.h"

GameEffect::GameEffect()
{
    this->sprite = CCSprite::create();
    this->animationObject = NULL;
    this->isStopped = false;
}

GameEffect::~GameEffect()
{
    
}

bool GameEffect::init()
{
    return true;
}
