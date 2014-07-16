//
//  Achievement.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/16/14.
//
//

#include "Achievement.h"

Achievement::Achievement()
{
    this->gold = 0;
    this->score = 0;
    this->time = 0;
}

Achievement::~Achievement()
{
    
}

void Achievement::addScore(int score)
{
    this->score += score;
}

void Achievement::addGold(int gold)
{
    this->gold += gold;
    
}



