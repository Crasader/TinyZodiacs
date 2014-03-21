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
    
}

PhysicBodyManager* PhysicBodyManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new PhysicBodyManager();
    }
    
    return instance;
}

void PhysicBodyManager::addBody(b2Body *body)
{
    this->listBody.push_back(body);
}

void PhysicBodyManager::update(float dt)
{
    if(this->world != NULL && this->world->IsLocked() == false)
    {
        for(int i=0 ; i< listBody.size() ; i++)
        {
            this->world->DestroyBody(listBody[i]);
        }
        this->listBody.clear();
    }
}