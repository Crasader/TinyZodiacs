//
//  SensorObject.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/21/14.
//
//

#include "SensorObject.h"
#include "Monster.h"
#include "Util.h"

SensorObject::SensorObject()
{
    this->body = NULL;
    this->jumpHeight = 10;
    this->moveSpeed = 2;
    this->direction = RIGHT;
    this->mustStop = true;
    this->isBack =false;
}

SensorObject::~SensorObject()
{
    
}

bool SensorObject::init()
{
    return true;
}

void SensorObject::update(float dt)
{
    GameObject::update(dt);
}

void SensorObject::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    
//    if(data->Data == this)
//    {
//        PhysicData* physicData = NULL;
//        if(isSideA)
//        {
//            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//        }
//        else
//        {
//            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//        }
// 
//    }
}

void SensorObject::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
//    if(data->Data == this)
//    {
//        
//    }
}

bool SensorObject::checkValidLaneID(int landID)
{
    if(this->listLaneID.size() == 0)
    {
        return true;
    }
    for(int i = 0; i < this->listLaneID.size(); i++)
    {
        if(listLaneID[i] == landID)
        {
            return true;
        }
    }
    return false;
}

