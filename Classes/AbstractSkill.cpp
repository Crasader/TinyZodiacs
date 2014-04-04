//
//  AbstractSkill.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#include "AbstractSkill.h"

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
