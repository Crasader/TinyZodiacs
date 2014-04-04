//
//  NormalProjectile.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/20/14.
//
//

#include "NormalProjectile.h"

NormalProjectile::NormalProjectile()
{
    contact_count=0;
    scheduled = false;
}

NormalProjectile::~NormalProjectile()
{
    
}

bool NormalProjectile::init()
{
    return true;
}

void NormalProjectile::BeginContact(b2Contact *contact)
{
//    CCLOG("Projectile begin");
    contact_count++;
    remove();

}

void NormalProjectile::EndContact(b2Contact *contact)
{
//    CCLOG("Projectile end");
    contact_count--;
    if(contact_count <= 0)
    {
//        CCLOG("Add to physyc manager");
        remove();
        contact_count=10;
//        scheduled = true;
    }
}

void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* data)
{
    
}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* data)
{
    
}

void NormalProjectile::remove()
{
//    PhysicBodyManager::getInstance()->addBody(this);
//    delete this;
    ScheduleManager::getInstance()->scheduleForGameObject(this, 2);

}

 void NormalProjectile::excuteScheduledFunction(CCObject* pSender, void *body)
{
    PhysicBodyManager::getInstance()->addBody((GameObject*)body);
//    ((GameObject*)body)->getSprite()->getParent()->removeChild(((GameObject*)body)->getSprite());
}

