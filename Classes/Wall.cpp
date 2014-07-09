//
//  Wall.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#include "Wall.h"

Wall::Wall()
{
    this->gameObjectID = WALL;
    this->deadWall = false;
}

Wall::~Wall()
{
    
}

void Wall::update(float dt)
{
    
}

bool Wall::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    return true;
}