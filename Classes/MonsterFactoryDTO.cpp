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
    this->listMonsterCreatorDTO = CCArray::create();
    this->listMonsterCreatorDTO->retain();
}

MonsterFactoryDTO::~MonsterFactoryDTO()
{
    CC_SAFE_RELEASE(this->listMonsterCreatorDTO);
}

bool MonsterFactoryDTO::init()
{
    return true;
}