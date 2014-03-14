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
   
    for(int i=0;i<5;i++)
    {
        CCSprite* background1 = CCSprite::createWithSpriteFrameName("background1.png");
        background1->setAnchorPoint(ccp(0,0));
       
     
        CCSprite* background2 = CCSprite::createWithSpriteFrameName("background2.png");
        background2->setAnchorPoint(ccp(0,0));
        CCSprite* background2_2 = CCSprite::createWithSpriteFrameName("background2.png");
        background2_2->setAnchorPoint(ccp(0,0));
        background2_2->setScale(2);
        CCSprite* background2_3 = CCSprite::createWithSpriteFrameName("background2.png");
        background2_3->setAnchorPoint(ccp(0,0));
        background2_3->setScale(3);
        CCSprite* background2_4 = CCSprite::createWithSpriteFrameName("background2.png");
        background2_4->setAnchorPoint(ccp(0,0));
        background2_4->setScale(4);
       

        
        CCSprite* background3 = CCSprite::createWithSpriteFrameName("background3.png");
        background3->setAnchorPoint(ccp(0,0));
        
        
        parallaxBackgroundNode->addChild(background1, 0, ccp(0.1f,1), ccp(0+(background1->getContentSize().width-1)*i,80));
        parallaxBackgroundNode->addChild(background2, 4, ccp(0.9f,1.09f), ccp(0+(background2->getContentSize().width-1)*i,84));
        parallaxBackgroundNode->addChild(background2_2, 3, ccp(0.6f,1.07f), ccp(0+(background2_2->getContentSize().width*background2_2->getScaleX()-1)*i,84));
        parallaxBackgroundNode->addChild(background2_3, 2, ccp(0.3f,1.05f), ccp(0+(background2_3->getContentSize().width*background2_3->getScaleX()-1)*i,84));
        parallaxBackgroundNode->addChild(background2_4, 1, ccp(0.2f,1.03f), ccp(0+(background2_4->getContentSize().width*background2_4->getScaleX()-1)*i,84));

        parallaxBackgroundNode->addChild(background3, 5, ccp(1,1), ccp(0+(background3->getContentSize().width-1)*i,-120));
//        
        parallaxBackgroundNode->setAnchorPoint(ccp(0,0));
        
        
        
       

    }
  
 
    
    this->addChild(parallaxBackgroundNode);
       return true;
    
}

void GameBackgroundLayer::scrollBackground(cocos2d::CCObject *pSender)
{
    CCPoint currentPos = parallaxBackgroundNode->getPosition();
    
    parallaxBackgroundNode->setPosition(currentPos.x+15   , currentPos.y+5);
    CCLOG("%f",parallaxBackgroundNode->getPositionX());
    
}
