//
//  GameObjectInfoView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "GameObjectInfoView.h"

GameObjectInfoView::GameObjectInfoView()
{
    
}

GameObjectInfoView::~GameObjectInfoView()
{
    
}

bool GameObjectInfoView::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    return true;
}

void GameObjectInfoView::attach(GameObject *gameObject)
{
    this->gameObject = gameObject;
}

void GameObjectInfoView::update(float dt)
{
    this->setPosition(this->gameObject->getPositionInPixel());
}

void GameObjectInfoView::setHealthBar(HealthBar *healthBar)
{
    this->healthBar = healthBar;
    this->addChild(healthBar, 0);
}

void GameObjectInfoView::setTextName(cocos2d::CCLabelTTF *textName)
{
    this->textName = textName;
    this->addChild(textName,1);
}