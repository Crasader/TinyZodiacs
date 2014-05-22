//
//  WaveDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/21/14.
//
//

#include "WaveDTO.h"

WaveDTO::WaveDTO()
{
    this->listMonsterFactoryDTO = CCArray::create();
    this->listMonsterFactoryDTO->retain();
    this->listItemCreatorDTO = CCArray::create();
    this->listItemCreatorDTO->retain();
}

WaveDTO::~WaveDTO()
{
    this->listMonsterFactoryDTO->release();
    this->listItemCreatorDTO->release();
}

bool WaveDTO::init()
{
    return true;
}