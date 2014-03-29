//
//  MapParallaxForeground.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#include "MapParallaxForeground.h"
MapParallaxForeground:: MapParallaxForeground()
{
    
}

MapParallaxForeground::~MapParallaxForeground()
{
    
}

bool MapParallaxForeground::init()
{
    if(!CCParallaxNode::create())
    {
        return false;
    }
    this->setAnchorPoint(ccp(0,0));
    return true;
}

void MapParallaxForeground::addForeground(std::string imageName, std::string spritesheetName, float ratio_x, float ratio_y, float layerIndex, float positionX, float positionY)
{
    //
    CCSprite* foreground = CCSprite::createWithSpriteFrameName(imageName.c_str());
    foreground->setAnchorPoint(ccp(0,0));
    
    this->addChild(foreground, layerIndex, ccp(ratio_x,ratio_y), ccp(positionX,positionY));
}