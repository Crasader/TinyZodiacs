//
//  NormalProjectile.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/20/14.
//
//

#include "NormalProjectile.h"

NormalProjectile::~NormalProjectile()
{
    if(this->getBody() != NULL)
    {
        this->getBody()->SetActive(false);
        this->getBody()->GetWorld()->DestroyBody(this->getBody());
    }
}

void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* data)
{
    switch (data->Id) {
        case PROJECTILE:
            delete this;
            break;
            
        default:
            break;
    }
}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* data)
{
    
}
