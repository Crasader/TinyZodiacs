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

}

TowerDTO::~TowerDTO()
{
}

bool TowerDTO::init()
{
    return true;
}

//////////////////////////////// TowerStructDTO ///////////////////////////////

TowerStructDTO::TowerStructDTO()
{
    this->group = A;
    this->id = "";
    this->positionX = 0;
    this->positionY = 0;
}

TowerStructDTO::~TowerStructDTO()
{
}

bool TowerStructDTO::init()
{
    return true;
}