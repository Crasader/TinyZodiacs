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
//    stopImmediately();
    if(excuteAction != NULL)
    {
        CCLOG("a-%d",excuteAction->retainCount());
//        if(excuteAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(excuteAction);
        }
       excuteAction->release();
        CCLOG("a-%d",excuteAction->retainCount());
    }
    if(stopAction != NULL)
    {
        CCLOG("b-%d",stopAction->retainCount());
//        if(stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(stopAction);
        }
        stopAction->release();
        CCLOG("b-%d",stopAction->retainCount());
    }
    if(coolDownAction != NULL)
    {
        CCLOG("c-%d",coolDownAction->retainCount());
//        if(coolDownAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(coolDownAction);
        }
            CCLOG("c-%d",coolDownAction->retainCount());
        coolDownAction->release();
    
    }
}

