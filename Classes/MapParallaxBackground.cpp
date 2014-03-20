//
//  MapParallaxBackground.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/19/14.
//
//

#include "MapParallaxBackground.h"

MapParallaxBackground:: MapParallaxBackground()
{
    
}

MapParallaxBackground::~MapParallaxBackground()
{
    
}

bool MapParallaxBackground::init()
{
    if(!CCParallaxNode::create())
    {
        return false;
    }
    this->setAnchorPoint(ccp(0,0));
    return true;
}

void MapParallaxBackground::addBackground(std::string imageName, std::string spritesheetName, float ratio_x, float ratio_y, float orderIndex, float width,float height)
{
    //
    CCSprite* background = CCSprite::createWithSpriteFrameName(imageName.c_str());
    CCSize size = background->getContentSize();
    
    int max = width/size.width + 1;
    
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create(spritesheetName.c_str());
    
    for(int i=0 ; i<max ; i++)
    {
        CCSprite* backgroundTemp = CCSprite::createWithSpriteFrameName(imageName.c_str());
        
        backgroundTemp->setAnchorPoint(ccp(0,0));
        backgroundTemp->setPosition(ccp(0+(background->getContentSize().width-1)*i,0));
        
        batchNode->addChild(backgroundTemp);
    }
   
    this->addChild(batchNode, orderIndex, ccp(ratio_x,ratio_y), ccp(0,0));
}