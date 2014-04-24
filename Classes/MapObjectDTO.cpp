//
//  MapObjectDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/17/14.
//
//

#include "MapObjectDTO.h"

MapObjectDTO::MapObjectDTO()
{
    this->id = "";
    this->imageName = "";
    this->bodyName = "";
    this->x = 0;
    this->y = 0;

    this->layerIndex = 0;
    this->canPass = true;
}

MapObjectDTO::~MapObjectDTO()
{
 
}

bool MapObjectDTO::init()
{
    return true;
}