//
//  WallDTO.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#include "WallDTO.h"

WallDTO::WallDTO()
{
    x = 0;
    y = 0;
    edge_x = 0;
    edge_y = 0;
    deadWall = false;
}

WallDTO::~WallDTO()
{
    
}

bool WallDTO::init()
{
    return true;
}