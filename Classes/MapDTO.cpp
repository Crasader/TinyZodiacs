//
//  MapDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/17/14.
//
//

#include "MapDTO.h"

MapDTO::MapDTO()
{
    this->listMapObject = CCArray::create();
    this->height = 0;
    this->width = 0;
    this->id = "";
}

MapDTO::~MapDTO()
{
    CC_SAFE_RELEASE(this->listMapObject);
}

bool MapDTO::init()
{
    return true;
}