//
//  PhysicBodyManager.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#include "PhysicBodyManager.h"

static PhysicBodyManager* instance;

PhysicBodyManager::PhysicBodyManager()
{

}

PhysicBodyManager::~PhysicBodyManager()
{
    for(int i=0 ; i< listBody.size() ; i++)
    {
        if(listBody[i] != NULL)
        {
            delete listBody[i];
        }
    }
}

bool PhysicBodyManager::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    return true;
}

void PhysicBodyManager::release()
{
    if(getInstance() != NULL)
    {
        delete getInstance();
    }
}

PhysicBodyManager* PhysicBodyManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new PhysicBodyManager();
    }
    
    return instance;
}

void PhysicBodyManager::addBody(GameObject *body)
{
    for(int i=0 ; i<this->listBody.size() ; i++)
    {
        if(body == listBody[i])
        {
            return;
        }
    }
    
//    CCLOG("New");
//    CCDelayTime *delayAction = CCDelayTime::create(0);
//    CCCallFuncND *callFuncSelector = CCCallFuncND::create(NULL, callfuncND_selector(PhysicBodyManager::addBodyToQueue), body);
//    this->runAction(CCSequence::create(delayAction,callFuncSelector));

    PhysicBodyManager::getInstance()->listBody.push_back((GameObject*)body);
}

void PhysicBodyManager::update(float dt)
{
    if(this->world != NULL && this->world->IsLocked() == false)
    {
        for(int i=0 ; i< listBody.size() ; i++)
        {
            if(listBody[i] != NULL && listBody[i]->getBody() != NULL)
            {
                
                    listBody[i]->getBody()->SetActive(false);
                
            
                    GameObject* data = listBody[i];
                  //  this->world->DestroyBody(listBody[i]->getBody());
                    //listBody[i]->setBody(NULL);
                    this->listBody.erase(this->listBody.begin()+i);
                    delete data;
    
            }
        }
//    this->listBody.clear();
    }
}