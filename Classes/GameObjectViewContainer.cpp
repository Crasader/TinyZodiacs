//
//  GameObjectViewContainer.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/15/14.
//
//

#include "GameObjectViewContainer.h"

GameObjectViewContainer::GameObjectViewContainer()
{
    this->listGameObjectView = CCArray::create();
    this->listGameObjectView->retain();
}

GameObjectViewContainer::~GameObjectViewContainer()
{
    this->listGameObjectView->release();
}

bool GameObjectViewContainer::init()
{
    if(!GameObjectView::init())
    {
        return false;
    }
    return true;
}

void GameObjectViewContainer::update(float dt)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listGameObjectView, object)
    {
        GameObjectView* gameObjectView = static_cast<GameObjectView*>(object);
        gameObjectView->update(dt);
    }
}

void GameObjectViewContainer::addGameObjectView(GameObjectView* gameObjectView)
{
    gameObjectView->attach(this->gameObject);
    this->listGameObjectView->addObject(gameObjectView);
    this->addChild(gameObjectView);
}

void GameObjectViewContainer::removeGameObjectView(GameObjectView* gameObjectView)
{
    if(this->listGameObjectView->indexOfObject(gameObjectView) != CC_INVALID_INDEX)
    {
        this->listGameObjectView->removeObject(gameObjectView);
    }
}
void GameObjectViewContainer::notifyChange()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listGameObjectView, object)
    {
        GameObjectView* gameObjectView = static_cast<GameObjectView*>(object);
        gameObjectView->notifyChange();
    }
}