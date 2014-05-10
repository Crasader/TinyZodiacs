//
//  PhysicBodyManager.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#include "GameObjectManager.h"

static GameObjectManager* instance = NULL;

GameObjectManager::GameObjectManager()
{
    this->listObjectRemoved = CCArray::create();
    this->listObjectRemoved->retain();
}

GameObjectManager::~GameObjectManager()
{
    CC_SAFE_RELEASE(this->listObjectRemoved);
}

bool GameObjectManager::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    this->scheduleUpdate();
    return true;
}

void GameObjectManager::release()
{
    if(getInstance() != NULL)
    {
        delete getInstance();
    }
}

GameObjectManager* GameObjectManager::getInstance()
{
    if(instance == NULL)
    {
        instance = GameObjectManager::create();
    }
    
    return instance;
}

void GameObjectManager::addObjectRemoved(GameObject *body)
{
//    if(this->listObjectRemoved->indexOfObject(body)!=CC_INVALID_INDEX)
//    {
        this->listObjectRemoved->addObject(body);
//    }
}

void GameObjectManager::update(float dt)
{
    this->listObjectRemoved->removeAllObjects();
}