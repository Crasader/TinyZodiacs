//
//  MonsterFactoryDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/29/14.
//
//

#include "MonsterFactoryDTO.h"

MonsterFactoryDTO::MonsterFactoryDTO()
{
    this->group = A;
    this->max = 0;
    this->listMonsterCreatorDTO = CCArray::create();
    this->listMonsterCreatorDTO->retain();
}

MonsterFactoryDTO::~MonsterFactoryDTO()
{
    this->listMonsterCreatorDTO->release();
}

bool MonsterFactoryDTO::init()
{
    return true;
}