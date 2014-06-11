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
    CCSize designSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
    CCSprite* background = CCSprite::createWithSpriteFrameName(imageName.c_str());
    CCSize size = background->getContentSize();
    

    
    float scaleDesignY = designSize.height/size.height;
    float scaleyyy = scaleDesignY + ratio_y*((height-designSize.height)/size.height);
    float scaleDesignX = designSize.width/size.width;
    float scalexxx = scaleDesignX + ratio_x*((width-designSize.width)/size.width);
    
    CCSpriteBatchNode* batchNode = CCSpriteBatchNode::createWithTexture(background->getTexture());
    CCSpriteBatchNode* batchNode1 = CCSpriteBatchNode::create(spritesheetName.c_str());
    
    if(batchNode->getTexture()->getName() != batchNode1->getTexture()->getName())
    {
        assert(0);
    }
    
    int max = width/size.width*scaleyyy + 1;
    
    for(int i=0 ; i<max ; i++)
    {
        CCSprite* backgroundTemp = CCSprite::createWithSpriteFrameName(imageName.c_str());
        backgroundTemp->setAnchorPoint(ccp(0,0));
        backgroundTemp->setPosition(ccp(0+(background->getContentSize().width*scaleyyy-1)*i,0));
        
       
    
//        backgroundTemp->setScaleX(scalexxx);
          backgroundTemp->setScale(scaleyyy);
        
        batchNode->addChild(backgroundTemp);
    }
   
    this->addChild(batchNode, orderIndex, ccp(ratio_x,ratio_y), ccp(0,0));
}