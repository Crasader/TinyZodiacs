//
//  HeroDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "HeroDTO.h"

HeroDTO::HeroDTO()
{
    this->resourcePack = NULL;
}
HeroDTO::~HeroDTO()
{
    if(this->resourcePack != NULL)
    {
        this->resourcePack->release();
    }
}

//////////////// HeroPreviewDTO ////////////////

HeroPreviewDTO::HeroPreviewDTO()
{
     locked = true;
}

HeroPreviewDTO::~HeroPreviewDTO()
{
    
}

bool HeroPreviewDTO::init()
{
    return true;
}