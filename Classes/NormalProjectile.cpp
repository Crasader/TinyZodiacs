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
}

void NormalProjectile::EndContact(b2Contact *contact)
{
    CCLOG("Projectile end");
    remove();
}

void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* data)
{

}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* data)
{
    
}

void NormalProjectile::remove()
{
    PhysicBodyManager::getInstance()->addBody(this->body);
    delete this;
}
