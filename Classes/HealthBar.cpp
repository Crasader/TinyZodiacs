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
    
    this->background = CCSprite::create("healthbar_background.png");
    this->background->setAnchorPoint(ccp(0.5,0.5));
    
    this->foreground = CCSprite::create("healthbar_foreground_red.png");
    this->foreground->setAnchorPoint(ccp(0,0.5));
    this->foreground->setPosition(ccp(-this->foreground->getContentSize().width/2,0));
    
    this->addChild(this->background);
    this->addChild(this->foreground);
    
    return true;
}

void HealthBar::setBackground(const char *imageName)
{
    this->background = CCSprite::createWithSpriteFrameName(imageName);
    this->background->setAnchorPoint(ccp(0.5,0.5));
    this->addChild(this->background,1);
}

void HealthBar::setForeground(const char *imageName)
{
    this->foreground = CCSprite::createWithSpriteFrameName(imageName);
    this->foreground->setAnchorPoint(ccp(0,0.5));
    this->foreground->setPosition(ccp(-this->foreground->getContentSize().width/2,0));
    this->addChild(this->foreground,2);

}

void HealthBar::updateProgress(float max, float current)
{
    float scale = current/max;
    scale = MAX(0, MIN(1, scale));
    this->foreground->setScaleX(scale);
    
}