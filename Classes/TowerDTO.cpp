//
//  TowerDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/26/14.
//
//

#include "TowerDTO.h"

TowerDTO::TowerDTO()
{
    this->group = "";
    this->id = "";
    this->positionX = 0;
    this->positionY = 0;
}

TowerDTO::~TowerDTO()
{
}

bool TowerDTO::init()
{
    return true;
}