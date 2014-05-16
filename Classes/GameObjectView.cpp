//
//  GameObjectInfoView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "GameObjectView.h"

GameObjectView::GameObjectView()
{
    
}

GameObjectView::~GameObjectView()
{
    
}

bool GameObjectView::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    return true;
}

void GameObjectView::attach(GameObject *gameObject)
{
    this->gameObject = gameObject;
}

void GameObjectView::update(float dt)
{
    this->setPosition(this->gameObject->getPositionInPixel());
}

