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
    this->x = 0;
    this->y = 0;
}

TowerDTO::~TowerDTO()
{
}

bool TowerDTO::init()
{
    return true;
}