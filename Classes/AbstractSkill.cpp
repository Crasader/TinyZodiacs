//
//  AbstractSkill.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#include "AbstractSkill.h"

#include "ScheduleManager.h"

AbstractSkill::~AbstractSkill()
{
    if(this->holder != NULL)
    {
        this->holder->release();
    }
}


void AbstractSkill::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, false);
    }
}

void AbstractSkill::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, false);
    }
}

void AbstractSkill::excuteImmediately()
{
    
}

void AbstractSkill::stopImmediately()
{
    
}

void AbstractSkill::setExcuteAble()
{
    
}

void AbstractSkill::stopAllAction()
{
    if(excuteAction != NULL)
    {
        if(excuteAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(excuteAction);
        }
        excuteAction->release();
    }
    if(stopAction != NULL)
    {
        if(stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(stopAction);
        }
        stopAction->release();
    }
    if(coolDownAction != NULL)
    {
        if(coolDownAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(coolDownAction);
        }
        coolDownAction->release();
    }
}

