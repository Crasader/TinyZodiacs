//
//  HealthBar.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/28/14.
//
//

#include "HealthBar.h"

HealthBar::HealthBar()
{
    
}

HealthBar::~HealthBar()
{
    
}

bool HealthBar::init()
{
    if(!CCNode::init())
    {
        return false;
    }

    
    this->background = CCSprite::createWithSpriteFrameName("healthbar_type_1.png");
    this->background->setAnchorPoint(ccp(0.5,0.5));
    
    this->foreground = CCSprite::createWithSpriteFrameName("healthbar_blue.png");
    this->foreground->setAnchorPoint(ccp(0,0.5));
    this->foreground->setPosition(ccp(-this->foreground->getContentSize().width/2,0));
 
    this->addChild(this->foreground);
    this->addChild(this->background);

    return true;
}

void HealthBar::setBackground(const char *imageName)
{
    this->background = CCSprite::createWithSpriteFrameName(imageName);
    this->background->setAnchorPoint(ccp(0,0.5));
    this->addChild(this->background,1);
}

void HealthBar::setForeground(const char *imageName)
{
    this->foreground = CCSprite::createWithSpriteFrameName(imageName);
    this->foreground->setAnchorPoint(ccp(0,0.5f));
    this->foreground->setPosition(ccp(-this->foreground->getContentSize().width/2,0));
    this->addChild(this->foreground,2);
}

void HealthBar::updateProgress(float max, float current)
{
    this->foreground->stopAllActions();
    float scale = current/max;
    scale = MAX(0, MIN(1, scale));
    this->foreground->runAction(CCScaleTo::create(0.2f, scale, 1));
}
