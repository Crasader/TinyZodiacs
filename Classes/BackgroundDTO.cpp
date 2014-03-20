//
//  BackgroundDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/19/14.
//
//

#include "BackgroundDTO.h"

BackgroundDTO::BackgroundDTO()
{
    this->imageName = "";
    this->spritesheetName = "";
    this->ratioX = 0;
    this->ratioY = 0;
    this->orderIndex = 0;
}

BackgroundDTO::~BackgroundDTO()
{
    
}

bool BackgroundDTO::init()
{
    return true;
}