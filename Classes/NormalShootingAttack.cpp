//
//  NormalShootingAttack.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#include "NormalShootingAttack.h"
NormalShootingAttack::~NormalShootingAttack()
{
    AbstractSkill::~AbstractSkill();

}

NormalShootingAttack::NormalShootingAttack(GameObject* holder)
{
    if(holder != NULL)
    {
        this->holder = holder;
        
        listProjectiles = CCArray::create();
        listProjectiles->retain();
    }
}


void NormalShootingAttack::excute()
{
    if(holder != NULL)
    {
        b2AABB aabb = holder->getBodyBoundingBox();
        
        b2PolygonShape rec;
        b2Vec2 vertices[4];
        vertices[0].Set( -1.0f,     0 );
        vertices[1].Set(     0, -0.1f );
        vertices[2].Set(  1.0f,     0 );
        vertices[3].Set(     0,  0.1f );
        rec.Set(vertices, 4);
        
        b2FixtureDef fixDef;
        fixDef.shape = &rec;
        fixDef.density = 0.24;
        fixDef.restitution=0.2;
        
        b2BodyDef bodyDef;
        bodyDef.type=b2_dynamicBody;
        bodyDef.bullet=true;
        if(holder->getDirection() == LEFT)
        {
            bodyDef.position.Set((this->holder->getPositionInPixel().x-aabb.lowerBound.x/2-100)/PTM_RATIO, this->holder->getPositionInPixel().y/PTM_RATIO);
        }
        else
        {
            bodyDef.position.Set((this->holder->getPositionInPixel().x+aabb.lowerBound.x/2+100)/PTM_RATIO, this->holder->getPositionInPixel().y/PTM_RATIO);
        }
        b2Body* body = this->holder->getBody()->GetWorld()->CreateBody(&bodyDef);
        body->CreateFixture(&fixDef);
        body->SetGravityScale(1.0f);
        //set data
        if(holder->getDirection() == LEFT)
        {
            body->ApplyForceToCenter(b2Vec2( -70,0));
        }
        else
        {
            body->ApplyForceToCenter(b2Vec2( 70,0));
        }
        
        //create projectile
        NormalProjectile* proj = new NormalProjectile();
        proj->setBody(body);
        
        PhysicData* data = new PhysicData();
        data->Id = PROJECTILE;
        data->Data = proj;
        
        body->SetUserData(data);
        
        listProjectiles->addObject(proj);
    }

}

void NormalShootingAttack::stop()
{
    
}

void NormalShootingAttack::Update(float dt)
{
    
}

void NormalShootingAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact)
{
    switch (data->Id)
    {
        case PROJECTILE:
            NormalProjectile* projectile = (NormalProjectile *)data->Data;
            projectile->BeginContact(contact);
            break;
    }
}

void NormalShootingAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact)
{
    switch (data->Id) {
        case PROJECTILE:
            break;
        default:
            break;
    }
}