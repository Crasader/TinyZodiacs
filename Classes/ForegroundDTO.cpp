//
//  ForegroundDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#include "ForegroundDTO.h"

ForegroundDTO::ForegroundDTO()
{
    this->imageName = "";
    this->ratioX = 0;
    this->ratioY = 0;
    this->layerIndex = 0;
    this->positionX = 0;
    this->positionY = 0;
}

ForegroundDTO::~ForegroundDTO()
{

}

bool ForegroundDTO::init()
{
    return true;
}