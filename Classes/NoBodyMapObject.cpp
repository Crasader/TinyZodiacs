//
//  NoBodyMapObject.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#include "NoBodyMapObject.h"

NoBodyMapObject::NoBodyMapObject()
{
    
}

NoBodyMapObject::~NoBodyMapObject()
{
    
}

void NoBodyMapObject::update(float dt)
{
    
}

void NoBodyMapObject::setPositionInPixel(const cocos2d::CCPoint &pos)
{
 
    this->sprite->setPosition(pos);
}

CCPoint NoBodyMapObject::getPositionInPixel()
{
    return this->sprite->getPosition();
}
