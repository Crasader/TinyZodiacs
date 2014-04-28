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
#include "CharacterAttackState.h"
#include "Util.h"
#include "Effect.h"



USING_NS_CC;

Character::Character()
{
    this->state = NULL;
    this->landing = 0;
    this->currentJumpCount = 0;
    
    this->normalAttack = NULL;
    this->skill1 = NULL;
    this->skill2 = NULL;
}

Character::~Character()
{
    //    delete normalAttack;
    //    delete skill1;
    //    delete skill2;
    normalAttack->release();
    skill1->release();
    skill2->release();
    
    
    this->footSensor->GetWorld()->DestroyBody(this->footSensor);
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
    move(direction, this->characterData.getSpeed());
}

void Character::jump()
{
    jump(this->characterData.getJumpHeight());
}

void Character::move(Direction direction, float speed)
{
    if(this->state->move())
    {
        b2Vec2 impulse = this->body->GetLinearVelocity();
        if(direction == LEFT)
        {
            impulse.x = -1*speed;
        }
        else
        {
            impulse.x = speed;
        }
        this->body->SetLinearVelocity(impulse);
        flipDirection(direction);
    }
}
void Character::jump(float force)
{
    if(this->currentJumpCount < this->characterData.getMaxJumpTimes())
    {
        if(this->state->jump())
        {
            changeState(new CharacterJumpState(this));
            
            b2Vec2 vel = this->body->GetLinearVelocity();
            vel.y = force;
            this->body->SetLinearVelocity( vel );
            
            this->currentJumpCount++;
        }
    }
    
}

void Character::attack()
{
    if(this->normalAttack->getIsExcutable() && this->state->attack())
    {
        changeState(new CharacterAttackState(this,this->normalAttack,this->attackAnimation));
    }
}

void Character::useSkill1()
{
    if(this->skill1->getIsExcutable() && this->state->attack())
    {
        changeState(new CharacterAttackState(this,this->skill1,this->skill1Animation));
    }
}

void Character::useSkill2()
{
    //    if(this->skill2->getIsExcutable() && this->state->attack())
    //    {
    //        changeState(new CharacterAttackState(this,this->skill2,this->skill2Animation));
    //    }
    
}

void Character::createFootSensor()
{
    b2AABB aabb = this->getBodyBoundingBox();
    
    b2PolygonShape rec;
    rec.SetAsBox((float32)abs(aabb.lowerBound.x)*5/10, (float32)FOOT_SENSOR_HEIGHT)/*, b2Vec2(0,aabb.lowerBound.y), 0)*/;
    
    b2FixtureDef fixDef;
    fixDef.shape = &rec;
    fixDef.isSensor = true;
    fixDef.density = WEIGHTLESS_DENSITY;
    
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

bool Character::isCharacterCanPassThoughMapObject(MapObject* mapObject)
{
    b2AABB footSensorAABB = Util::getBodyBoundingBoxDynamic(this->footSensor);
    b2AABB mapObjectAABB = Util::getBodyBoundingBoxDynamic(mapObject->getBody());
    
    if( this->body->GetLinearVelocity().y > 3 || Util::bodiesArePassingThrough(mapObject->getBody(), this->body) || (!Util::bodiesAreTouching(this->footSensor, mapObject->getBody()) &&!(mapObjectAABB.lowerBound.x < footSensorAABB.lowerBound.x && footSensorAABB.upperBound.x < mapObjectAABB.upperBound.x) && mapObjectAABB.upperBound.y - footSensorAABB.upperBound.y > ((20*1.0f)/32)))
    {
        return true;
        
    }
    
    return false;
}

void Character::stopMove()
{
    this->body->SetLinearVelocity(b2Vec2(0, this->getBody()->GetLinearVelocity().y));
}

void Character::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    
    if(data->Data == this)
    {
        PhysicData* physicData = NULL;
        if(isSideA)
        {
            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        }
        
        switch (data->Id)
        {
            case CHARACTER_FOOT_SENSOR:
            {
                if(physicData!=NULL)
                {
                    switch (physicData->Id) {
                        case MAP_BASE:
                        {
                            GameObject* mapObject = (GameObject*)physicData->Data;
                            if(!Util::bodiesArePassingThrough(mapObject->getBody(), this->body))
                            {
                                this->landing ++;
                                CCLOG("landing first");
                                this->currentJumpCount =0;
                            }
                        }
                            break;
                            
                        default:
                            break;
                    }
                }
                
            }
                break;
            case CHARACTER_BODY:
            {
                
                if(physicData!=NULL)
                {
                    
                    switch (physicData->Id) {
                        case MAP_BASE:
                        {
                            MapObject* mapObject = (MapObject*)physicData->Data;
                            if (!Util::bodiesArePassingThrough(this->body, mapObject->getBody())) {
                                this->isLanding = true;
                            }
                           
                            if(landing == 0 && !Util::bodiesArePassingThrough(this->body, mapObject->getBody()) && Util::bodiesAreTouching(this->footSensor, mapObject->getBody()))
                            {
                                landing++;
                                CCLOG("landing second");
                                this->currentJumpCount =0;
                            }

                            if(isCharacterCanPassThoughMapObject(mapObject) && mapObject->getCanPass() == true)
                            {
                                contact->SetEnabled(false);
                            }
                        }
                            break;
                            
                        default:
                            
                            break;
                    }
                    
                }
                
            }
                break;
                
                
            default:
                break;
        }
        ///
        
    }
}

void Character::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data->Data == this)
    {
        PhysicData* physicData = NULL;
        if(isSideA)
        {
            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        }
        
        switch (data->Id) {
            case CHARACTER_FOOT_SENSOR:
            {
                if(physicData!=NULL)
                {
                    switch (physicData->Id) {
                        case MAP_BASE:
                        {
                            //                            GameObject* mapObject = (GameObject*)physicData->Data;
                            //                            if(!Util::bodiesArePassingThrough(mapObject->getBody(), this->body))
                            //                            {
                            //                                this->landing ++;
                            //                                this->currentJumpCount =0;
                            //                            }
                            
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
                
                break;
                
            case CHARACTER_BODY:
            {
                PhysicData* physicData = NULL;
                if(isSideA)
                {
                    physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
                }
                else
                {
                    physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
                }
                
                if(physicData != NULL)
                {
                    switch (physicData->Id) {
                            
                        case MAP_BASE:
                        {
                                                   //                            if (!Util::bodiesArePassingThrough(this->body, mapObject->getBody())) {
                            //                                this->isLanding = true;
                            //                            }
                        }
                            break;
                            
                        default:
                            break;
                    }
                }
                
            }
                break;
                
            default:
                break;
        }
        ///
        contact->SetEnabled(true);
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

void Character::setGroup(uint16 group)
{
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

void Character::notifyByEffect(CCObject* effect)
{
    this->characterData.setHealth(this->characterData.getHealth()+((Effect*)effect)->getHealth());
    //    if(this->characterData.getHealth()<=0)
    //    {
    //        PhysicBodyManager::getInstance()->addBody(this);
    //    }
}
