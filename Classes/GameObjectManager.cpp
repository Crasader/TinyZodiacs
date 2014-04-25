//
//  PhysicBodyManager.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#include "GameObjectManager.h"

static GameObjectManager* instance;

GameObjectManager::GameObjectManager()
{
    this->listBody = CCArray::create();
    this->listBody->retain();
}

GameObjectManager::~GameObjectManager()
{
//    for(int i=0 ; i< listBody.size() ; i++)
//    {
//        if(listBody[i] != NULL)
//        {
//            delete listBody[i];
//        }
//    }
    listBody->removeAllObjects();
    listBody->release();
}

bool GameObjectManager::init()
{
    if(!CCNode::init())
    {
        return false;
    }
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
        instance = new GameObjectManager();
    }
    
    return instance;
}

void GameObjectManager::addObject(GameObject *body)
{
//    for(int i=0 ; i<this->listBody->count() ; i++)
//    {
//        if(body == listBody->objectAtIndex(i))
//        {
//            return;
//        }
//    }
    GameObjectManager::getInstance()->listBody->addObject(body);
    CCLOG("%d", GameObjectManager::getInstance()->listBody->count());
}

void GameObjectManager::update(float dt)
{
    if(this->world != NULL && this->world->IsLocked() == false)
    {
        this->listBody->removeAllObjects();
    }
}