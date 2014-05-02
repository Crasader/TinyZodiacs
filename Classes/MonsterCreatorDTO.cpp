//
//  MonsterCreatorDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/29/14.
//
//

#include "MonsterCreatorDTO.h"

MonsterCreatorDTO::MonsterCreatorDTO()
{
    this->delayPerUnit = 0;
    this->delay = 0;
    this->positionX = 0;
    this->positionY = 0;
}

MonsterCreatorDTO::~MonsterCreatorDTO()
{
    this->listMonsterID.clear();
}

bool MonsterCreatorDTO::init()
{
    return true;
}