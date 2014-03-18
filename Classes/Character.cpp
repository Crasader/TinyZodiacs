//
//  Character.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 2/13/14.
//
//

#include "Character.h"
#include "AnimationFactory.h"
#include "Box2D/Box2D.h"
#include "CharacterMidAirState.h"
#include "CharacterJumpState.h"
#include "CharacterIdleState.h"



USING_NS_CC;

Character::Character()
{
    this->speed = 5;
    this->state = NULL;
    
    
    runAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-run");
    attackAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-attack");
    jumpAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-jump");
    idleAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-idle");
    fallAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-fall");
    flyAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-fly");
    skill1Animation = AnimationFactory::getSharedFactory()->getAnimationObjectByName("monkey-skill");
    
    //create attack skill
}

Character::~Character()
{
    
}

void Character::changeState(CharacterState *states)
{
    if(this->state != NULL)
    {
        this->state->onExitState();
        delete this->state;
        this->state = NULL;
    }
    this->state = states;
    this->state->onEnterState();
}

b2Joint* joint;
void Character::setSkin(b2Body *body, CCSprite *sprite)
{
    GameObject::setSkin(body, sprite);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2FixtureDef fixtureDef;
    createFootSensor();
    this->changeState(new CharacterIdleState(this));
}


bool falling = false;
void Character::update(float dt)
{
    this->state->update(dt);
    GameObject::update(dt);
}

void Character::move(Direction direction)
{
    if(this->state->move())
    {
        b2Vec2 impulse = this->body->GetLinearVelocity();
        if(direction == LEFT)
        {
            impulse.x = -5;
        }
        else
        {
            impulse.x = 5;
        }
        this->body->SetLinearVelocity(impulse);
        flipDirection(direction);
    }

}

void Character::jump()
{
    if(this->state->jump())
    {
 

        b2Vec2 vel = this->body->GetLinearVelocity();
        vel.y = 10;
        this->body->SetLinearVelocity( vel );
    }
   
    //
}

void Character::attack()
{
    this->state->attack();
}

void Character::useSkill1()
{
    
}

void Character::useSkill2()
{
    
}

void Character::createFootSensor()
{
    //Calculate b
//    b2AABB aabb;
//    aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
//    aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
//    b2Fixture* fixture = this->body->GetFixtureList();
//    while (fixture != NULL)
//    {
//        aabb.Combine(aabb, fixture->GetAABB(0));
//        fixture = fixture->GetNext();
//    }

    b2AABB aabb = this->getBodyBoundingBox();
    
    b2PolygonShape rec;
    rec.SetAsBox((float32)FOOT_SENSOR_WIDTH, (float32)FOOT_SENSOR_HEIGHT)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
    
    b2FixtureDef fixDef;
    fixDef.shape = &rec;
    fixDef.isSensor = true;
    fixDef.density = WEIGHTLESS_DENSITY;
    fixDef.userData = (void*)"foot";
    
    b2BodyDef bodyDef;
    bodyDef.type=b2_dynamicBody;
    bodyDef.bullet=true;
    bodyDef.position.Set(0/PTM_RATIO, 0/32);
    footSensor = this->body->GetWorld()->CreateBody(&bodyDef);
    footSensor->CreateFixture(&fixDef);
    
    //create joint
    b2RevoluteJointDef footBodyJoint;
    footBodyJoint.bodyA = this->body;
    footBodyJoint.bodyB = this->footSensor;
    footBodyJoint.collideConnected =false;
    footBodyJoint.localAnchorA.Set(0, aabb.lowerBound.y);
    
    this->body->GetWorld()->CreateJoint(&footBodyJoint);
}

void Character::stopMove()
{
    this->body->SetLinearVelocity(b2Vec2(0, this->getBody()->GetLinearVelocity().y));
}

void Character::BeginContact(b2Contact *contact)
{
    this->normalAttack->BeginContact(contact);
}
void Character::EndContact(b2Contact *contact)
{
    this->normalAttack->EndContact(contact);
}
