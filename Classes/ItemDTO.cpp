//
//  ItemDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "ItemDTO.h"

ItemDTO::ItemDTO()
{
    this->imageName = "";
    this->bodyName = "";
    this->animation = "";
    this->positionX = 0;
    this->positionY = 0;
    this->lifeTime = 0;
}

ItemDTO::~ItemDTO()
{
    
}

bool ItemDTO::init()
{
    return true;
}