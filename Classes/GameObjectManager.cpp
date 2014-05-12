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
    this->listGameObject = CCArray::create();
    this->listGameObject->retain();
}

GameObjectManager::~GameObjectManager()
{
    CC_SAFE_RELEASE(this->listObjectRemoved);
    CC_SAFE_RELEASE(this->listGameObject);
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

void GameObjectManager::addGameObject(GameObject* object)
{
    this->listGameObject->addObject(object);
}

void GameObjectManager::update(float dt)
{
    this->listObjectRemoved->removeAllObjects();
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listGameObject, object)
    {
        GameObject* gameObject = static_cast<GameObject*>(object);
        gameObject->update(dt);
    }
}