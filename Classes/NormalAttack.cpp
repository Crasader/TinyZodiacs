//
//  NormalAttack.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#include "NormalAttack.h"

NormalAttack::NormalAttack()
{
    
}

NormalAttack::NormalAttack(GameObject* holder)
{
    if(holder != NULL)
    {
        this->holder = holder;
        
        b2PolygonShape rec;
        rec.SetAsBox((float32)200/PTM_RATIO, (float32)200/PTM_RATIO)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
        
        b2FixtureDef fixDef;
        fixDef.shape = &rec;
        fixDef.isSensor = true;
        fixDef.density = WEIGHTLESS_DENSITY;
        fixDef.userData = (void*)"foot";
        
        b2BodyDef bodyDef;
        bodyDef.type=b2_dynamicBody;
        bodyDef.bullet=true;
        bodyDef.position.Set(0/PTM_RATIO, 0/32);
        this->skillSensor = this->holder->getBody()->GetWorld()->CreateBody(&bodyDef);
        this->skillSensor->CreateFixture(&fixDef);
        
        //
        //create joint
        b2RevoluteJointDef footBodyJoint;
        footBodyJoint.bodyA = this->holder->getBody();
        footBodyJoint.bodyB = this->skillSensor;
        footBodyJoint.collideConnected =false;
        
        b2AABB aabb = this->holder->getBodyBoundingBox();
        footBodyJoint.localAnchorA.Set(aabb.lowerBound.x/2,0);
        
        this->holder->getBody()->GetWorld()->CreateJoint(&footBodyJoint);
        
        this->skillSensor->SetActive(false);
    }
}

NormalAttack::~NormalAttack()
{
    
}

void NormalAttack::excute()
{
    this->skillSensor->SetActive(true);
}
void NormalAttack::stop()
{
    this->skillSensor->SetActive(false);
}

void NormalAttack::BeginContact(b2Contact *contact)
{
    //    if(contact->GetFixtureA() == footSensor->GetFixtureList() || contact->GetFixtureB() == footSensor->GetFixtureList())
    //    {
    //        changeState(new CharacterIdleState(this));
    //    }
    if((contact->GetFixtureA() == this->skillSensor->GetFixtureList()) || (contact->GetFixtureB() == this->skillSensor->GetFixtureList()))
    {
        CCLOG("skill BeginContact");
    }
}

void NormalAttack::EndContact(b2Contact *contact)
{
    if((contact->GetFixtureA() == this->skillSensor->GetFixtureList()) || (contact->GetFixtureB() == this->skillSensor->GetFixtureList()))
    {
        CCLOG("skill EndContact");
    }
    
}

void NormalAttack::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    if((contact->GetFixtureA() == this->skillSensor->GetFixtureList()) || (contact->GetFixtureB() == this->skillSensor->GetFixtureList()))
    {
        CCLOG("skill PreSolve");
    }
    
}

void NormalAttack::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    if((contact->GetFixtureA() == this->skillSensor->GetFixtureList()) || (contact->GetFixtureB() == this->skillSensor->GetFixtureList()))
    {
        CCLOG("skill PostSolve");
    }
    
}

