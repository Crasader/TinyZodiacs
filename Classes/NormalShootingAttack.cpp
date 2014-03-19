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
        
//        b2PolygonShape rec;
//        rec.SetAsBox((float32)10/PTM_RATIO, (float32)10/PTM_RATIO)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
        
        b2FixtureDef fixDef;
        fixDef.shape = &rec;
        fixDef.density = 0.24;
        fixDef.restitution=0.2;

        //        fixDef.userData = (void*)"foot";
        
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
    }

}

void NormalShootingAttack::stop()
{
    
}

void NormalShootingAttack::BeginContact(b2Contact *contact)
{
    
}

void NormalShootingAttack::EndContact(b2Contact *contact)
{
    
}
