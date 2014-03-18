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
}

MapObjectDTO::~MapObjectDTO()
{
 
}

bool MapObjectDTO::init()
{
    return true;
}