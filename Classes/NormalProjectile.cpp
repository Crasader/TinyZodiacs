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
    CCLOG("Projectile begin");
    contact_count++;
    remove();

}

void NormalProjectile::EndContact(b2Contact *contact)
{
    CCLOG("Projectile end");
    contact_count--;
    if(contact_count <= 0)
    {
        remove();
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
    PhysicBodyManager::getInstance()->addBody(this);
//    delete this;
}
