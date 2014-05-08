//
//  Item.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "Item.h"

Item::Item()
{
    
}

Item::~Item()
{
    
}

bool Item::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    return true;
}

