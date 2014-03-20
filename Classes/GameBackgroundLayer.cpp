//
//  GameBackgroundLayer.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/7/14.
//
//

#include "GameBackgroundLayer.h"


USING_NS_CC;

GameBackgroundLayer::GameBackgroundLayer()
{
    parallaxBackgroundNode = CCParallaxNode::create();
    parallaxBackgroundNode2 =CCParallaxNode::create();
}

GameBackgroundLayer::~GameBackgroundLayer()
{
    
}

bool GameBackgroundLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
   
       return true;
    
}

void GameBackgroundLayer::scrollBackground(cocos2d::CCObject *pSender)
{
    CCPoint currentPos = parallaxBackgroundNode->getPosition();
    
    parallaxBackgroundNode->setPosition(currentPos.x+15   , currentPos.y+5);
    CCLOG("%f",parallaxBackgroundNode->getPositionX());
    
}
