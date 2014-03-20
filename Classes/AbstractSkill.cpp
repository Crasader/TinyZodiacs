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
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetUserData();
        checkCollisionDataInBeginContact(data, contact);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetUserData();
        checkCollisionDataInBeginContact(data, contact);
    }
}

void AbstractSkill::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetUserData();
        checkCollisionDataInEndContact(data, contact);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetUserData();
        checkCollisionDataInEndContact(data, contact);
    }
}