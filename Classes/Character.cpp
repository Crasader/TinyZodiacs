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
#include "Util.h"


USING_NS_CC;

Character::Character()
{
    this->state = NULL;
    this->landing = 0;
    this->currentJumpCount = 0;
}

Character::~Character()
{
    delete normalAttack;
    delete skill1;
    delete skill2;
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
    //create foot sensor
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2FixtureDef fixtureDef;
    createFootSensor();
    this->changeState(new CharacterIdleState(this));

    //set body data
    PhysicData* scharacterData = new PhysicData();
    scharacterData->Id = CHARACTER_BODY;
    scharacterData->Data = this;
    this->getBody()->SetUserData(scharacterData);
}

void Character::setOriginCharacterData(CharacterData data)
{
    this->originCharacterData = data;
    this->characterData = this->originCharacterData;
}


bool falling = false;
void Character::update(float dt)
{
    //
    if(this->normalAttack != NULL)
    {
        this->normalAttack->update(dt);
    }
    if(this->skill1 != NULL)
    {
        this->skill1->update(dt);
    }
    if(this->skill2 != NULL)
    {
        this->skill2->update(dt);
    }
    //
    this->state->update(dt);
    GameObject::update(dt);
    //
    if(this->body->GetLinearVelocity().x >=2)
    {
        flipDirection(RIGHT);
    }
    else if(this->body->GetLinearVelocity().x <=-2)
    {
        flipDirection(LEFT);
    }
}

void Character::move(Direction direction)
{
    if(this->state->move())
    {
        b2Vec2 impulse = this->body->GetLinearVelocity();
        if(direction == LEFT)
        {
            impulse.x = -1*this->characterData.getSpeed();
        }
        else
        {
            impulse.x = this->characterData.getSpeed();
        }
        this->body->SetLinearVelocity(impulse);
        flipDirection(direction);
    }
    
}

void Character::jump()
{
    if(this->currentJumpCount < this->characterData.getMaxJumpTimes())
    {
        if(this->state->jump())
        {
            b2Vec2 vel = this->body->GetLinearVelocity();
            vel.y = this->characterData.getJumpHeight();
            this->body->SetLinearVelocity( vel );
            
            this->currentJumpCount++;
        }
    }
    //
}

void Character::attack()
{
    if(this->normalAttack->getIsExcutable())
    {
        this->state->attack();
    }
}

void Character::useSkill1()
{
    if(this->normalAttack->getIsExcutable())
    {
        this->state->attack();
    }
}

void Character::useSkill2()
{
    if(this->normalAttack->getIsExcutable())
    {
        this->state->attack();
    }
}

void Character::createFootSensor()
{
    b2AABB aabb = this->getBodyBoundingBox();
    
    b2PolygonShape rec;
    rec.SetAsBox((float32)abs(aabb.lowerBound.x)*9/10, (float32)FOOT_SENSOR_HEIGHT)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
    
    b2FixtureDef fixDef;
    fixDef.shape = &rec;
    fixDef.isSensor = true;
    fixDef.density = WEIGHTLESS_DENSITY;
    
    //    PhysicData* sensorData = new PhysicData();
    //    sensorData->Id = CHARACTER_FOOT_SENSOR;
    //    sensorData->Data = this;
    //    fixDef.userData = (void*)sensorData;
    //
    
    b2BodyDef bodyDef;
    bodyDef.type=b2_dynamicBody;
    bodyDef.bullet=true;
    bodyDef.position.Set(0/PTM_RATIO, 0/PTM_RATIO);
    footSensor = this->body->GetWorld()->CreateBody(&bodyDef);
    footSensor->CreateFixture(&fixDef);
    
    //create joint
    b2RevoluteJointDef footBodyJoint;
    footBodyJoint.bodyA = this->body;
    footBodyJoint.bodyB = this->footSensor;
    footBodyJoint.collideConnected =false;
    footBodyJoint.localAnchorA.Set((aabb.lowerBound.x+aabb.upperBound.x)/2, aabb.lowerBound.y);
    
    //Set foot sensor bullet
    this->footSensor->SetBullet(true);
    
    //
    PhysicData* sensorData = new PhysicData();
    sensorData->Id = CHARACTER_FOOT_SENSOR;
    sensorData->Data = this;
    footSensor->SetUserData(sensorData);
    
    this->body->GetWorld()->CreateJoint(&footBodyJoint);
}

void Character::stopMove()
{
    this->body->SetLinearVelocity(b2Vec2(0, this->getBody()->GetLinearVelocity().y));
}

void Character::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data->Data == this)
    {
        switch (data->Id)
        {
            case CHARACTER_FOOT_SENSOR:
                if(this == data->Data)
                {
                    this -> landing ++;
                    this-> currentJumpCount =0;
                }
                break;
                
            default:
                break;
        }
    }
}

void Character::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data->Data == this)
    {
        switch (data->Id) {
            case CHARACTER_FOOT_SENSOR:
                if(this == data->Data)
                {
                    this -> landing --;
                    if(this->landing <0)
                    {
                        this->landing =0;
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

void Character::BeginContact(b2Contact *contact)
{
    GameObject::BeginContact(contact);
    
    if(normalAttack != NULL)
    {
        normalAttack->BeginContact(contact);
    }
    
    if(skill2 != NULL)
    {
        skill2->BeginContact(contact);
    }
    
    if(skill1 != NULL)
    {
        skill1->BeginContact(contact);
    }
}

void Character::EndContact(b2Contact *contact)
{
    GameObject::EndContact(contact);
    
    if(normalAttack != NULL)
    {
        normalAttack->EndContact(contact);
    }
    
    if(skill1 != NULL)
    {
        skill1->EndContact(contact);
    }
    
    if(skill2 != NULL)
    {
        skill2->EndContact(contact);
    }
}

void Character::setGroup(int group)
{
    //    b2Filter data = this->footSensor->GetFixtureList()[0].GetFilterData();
    //    data.groupIndex = group;
    //    this->footSensor->GetFixtureList()[0].SetFilterData(data);
    for (b2Fixture* f = this->footSensor->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            Util::setFixtureGroup(f, GROUP_SENSOR);
        }
    }
    
    
    if(this->normalAttack != NULL)
    {
        this->normalAttack->setGroup(GROUP_SKILL_DEFAULT);
    }
    
    if(this->skill1 != NULL)
    {
        this->skill1->setGroup(GROUP_SKILL_DEFAULT);
    }

    if(this->skill2 != NULL)
    {
        this->skill2->setGroup(GROUP_SKILL_DEFAULT);
    }

    
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            Util::setFixtureGroup(f, group);
            
            if(f->GetNext() != NULL)
            {
                b2Filter filter = f->GetFilterData();
                filter.maskBits = filter.maskBits ^ GROUP_SKILL_DEFAULT;
                f->SetFilterData(filter);
            }
        }
    }
}
