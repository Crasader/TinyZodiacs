//
//  SensorObjectDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/22/14.
//
//

#include "SensorObjectDTO.h"

SensorObjectDTO::SensorObjectDTO()
{
    this->jumpHeight = 0;
    this->moveSpeed = 0;
    this->mustStop = false;
    this->isBack = false;
    this->direction = LEFT;
    this->x = 0;
    this->y = 0;
    this->edge_x = 0;
    this->edge_y = 0;
    this->listLaneID.clear();
}

SensorObjectDTO::~SensorObjectDTO()
{
    this->listLaneID.clear();
}

bool SensorObjectDTO::init()
{
    return true;
}