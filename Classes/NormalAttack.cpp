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
        rec.SetAsBox((float32)100/PTM_RATIO, (float32)100/PTM_RATIO)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
        
        b2FixtureDef fixDef;
        fixDef.shape = &rec;
        fixDef.isSensor = true;
        fixDef.density = WEIGHTLESS_DENSITY;
        //        fixDef.userData = (void*)"foot";
        
        b2BodyDef bodyDef;
        bodyDef.type=b2_dynamicBody;
        bodyDef.bullet=true;
        bodyDef.position.Set(0/PTM_RATIO, 0/PTM_RATIO);
        bodyDef.fixedRotation = true;
        
        this->data.setSkillSensor(this->holder->getBody()->GetWorld()->CreateBody(&bodyDef));
        this->data.getSkillSensor()->CreateFixture(&fixDef);
        
        
        //
        //create joint
        b2RevoluteJointDef footBodyJoint;
        footBodyJoint.bodyA = this->holder->getBody();
        footBodyJoint.bodyB = this->data.getSkillSensor();
        footBodyJoint.collideConnected =false;
        
        b2AABB aabb = this->holder->getBodyBoundingBox();
        footBodyJoint.localAnchorA.Set(aabb.upperBound.x,0);
        footBodyJoint.localAnchorB.Set((float32)100/PTM_RATIO,0);
        
        
        this->holder->getBody()->GetWorld()->CreateJoint(&footBodyJoint);
        
        this->data.getSkillSensor()->SetActive(false);
        //set data
    }
}

NormalAttack::~NormalAttack()
{

}


void NormalAttack::BeginContact(b2Contact *contact)
{
    CCLOG("Attack begin");
}

void NormalAttack::EndContact(b2Contact *contact)
{
    CCLOG("Attack end");
}

void NormalAttack::update(float dt)
{
    
}

void NormalAttack::excute()
{
    this->data.getSkillSensor()->SetActive(true);   
}

void NormalAttack::stop()
{
    this->data.getSkillSensor()->SetActive(false);
}

void NormalAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact)
{
    
}

void NormalAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact)
{
    
}

