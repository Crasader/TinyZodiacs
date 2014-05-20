//
//  Character.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 2/13/14.
//
//

#include "Character.h"
#include "AnimationLoader.h"
#include "Box2D/Box2D.h"
#include "CharacterMidAirState.h"
#include "CharacterJumpState.h"
#include "CharacterIdleState.h"
#include "CharacterAttackState.h"
#include "Util.h"
#include "Effect.h"
#include "HealthPointEffect.h"
#include "EffectManager.h"



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
//    this->footSensor->GetWorld()->DestroyBody(this->footSensor);
    
    
    if(normalAttack)
    {
        normalAttack->release();
        normalAttack = NULL;
    }
    
    if(skill1)
    {
        skill1->release();
        skill1 = NULL;
    }
    
    if(skill2)
    {
        skill2->release();
        skill2 = NULL;
    }
}

void Character::changeState(CharacterState *states)
{
    if(this->state != NULL)
    {
        this->state->onExitState();
        this->state->release();
        this->state = NULL;
    }
    this->state = states;
    this->state->onEnterState();
}

b2Joint* joint;
void Character::setSkin(b2Body *body, CCSprite *sprite)
{
    GameObject::setSkin(body, sprite);
    //set body data
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            //set body data
            PhysicData* scharacterData = new PhysicData();
            scharacterData->BodyId = CHARACTER_BODY;
            scharacterData->Data = this;
            scharacterData->GameObjectID = this->gameObjectID;
            
            if(f->GetNext() != NULL)
            {
                scharacterData->FixtureId = BODY_SUB_FIXTURE;
            }
            else
            {
                scharacterData->FixtureId = BODY_MAIN_FIXTURE;
            }
            
            
            f->SetUserData(scharacterData);
        }
    }
    //create foot sensor
    createFootSensor();
    
}

void Character::onCreate()
{

    this->changeState(new CharacterIdleState(this));
}

void Character::setOriginCharacterData(CharacterData data)
{
    //    data.setAttack(0);
    this->originCharacterData = data;
    this->characterData = this->originCharacterData;
}

void Character::update(float dt)
{
    GameObject::update(dt);
    this->state->update(dt);
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

    if(this->body->GetLinearVelocity().x >=2)
    {
        flipDirection(RIGHT);
    }
    else if(this->body->GetLinearVelocity().x <=-2)
    {
        flipDirection(LEFT);
    }
    if(isDead() == true)
    {
        destroy();
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
    if(this->normalAttack->getIsExcutable() && this->state->attack() && isDead() == false)
    {
        changeState(new CharacterAttackState(this,this->normalAttack,this->attackAnimation));
    }
}

void Character::useSkill1()
{
    if(this->skill1->getIsExcutable() && this->state->attack() && isDead() == false && isDead() == false)
    {
        changeState(new CharacterAttackState(this,this->skill1,this->skill1Animation));
    }
}

void Character::useSkill2()
{
    //    if(this->skill2->getIsExcutable() && this->state->attack() && isDead() == false)
    //    {
    //        changeState(new CharacterAttackState(this,this->skill2,this->skill2Animation));
    //    }
    
}

void Character::createFootSensor()
{
    b2AABB aabb = this->getBodyBoundingBox();
    
    b2PolygonShape rec;
    rec.SetAsBox((float32)abs(aabb.lowerBound.x)*5/10, (float32)FOOT_SENSOR_HEIGHT, b2Vec2(0,aabb.lowerBound.y), 0);
    
    b2FixtureDef fixDef;
    fixDef.shape = &rec;
    fixDef.isSensor = true;
    fixDef.density = WEIGHTLESS_DENSITY;
    
    PhysicData* sensorData = new PhysicData();
    sensorData->BodyId = CHARACTER_FOOT_SENSOR;
    sensorData->Data = this;
    sensorData->GameObjectID = this->gameObjectID;
    sensorData->FixtureId = FOOT_SENSOR_FIXTURE;
    fixDef.userData = sensorData;

    this->footSensor = this->body->CreateFixture(&fixDef);
//    b2BodyDef bodyDef;
//    bodyDef.type=b2_dynamicBody;
//    bodyDef.bullet=true;
//    bodyDef.position.Set(0/PTM_RATIO, 0/PTM_RATIO);
//    footSensor = this->body->GetWorld()->CreateBody(&bodyDef);
//    footSensor->CreateFixture(&fixDef);
    
//    //create joint
//    b2RevoluteJointDef footBodyJoint;
//    footBodyJoint.bodyA = this->body;
//    footBodyJoint.bodyB = this->footSensor;
//    footBodyJoint.collideConnected =false;
//    footBodyJoint.localAnchorA.Set((aabb.lowerBound.x+aabb.upperBound.x)/2, aabb.lowerBound.y);
//    
//    //Set foot sensor bullet
//    this->footSensor->SetBullet(true);
//    
//    //
//    PhysicData* sensorData = new PhysicData();
//    sensorData->BodyId = CHARACTER_FOOT_SENSOR;
//    sensorData->Data = this;
//    sensorData->GameObjectID = this->gameObjectID;
//
//    footSensor->SetUserData(sensorData);
//    
//    this->body->GetWorld()->CreateJoint(&footBodyJoint);
}

bool Character::isCharacterCanPassThoughMapObject(MapObject* mapObject)
{
//    b2AABB footSensorAABB = Util::getBodyBoundingBoxDynamic(this->footSensor);
//    b2AABB mapObjectAABB = Util::getBodyBoundingBoxDynamic(mapObject->getBody());
//    
//    if( this->body->GetLinearVelocity().y > 3 || Util::bodiesArePassingThrough(mapObject->getBody(), this->body) || (!Util::bodiesAreTouching(this->footSensor, mapObject->getBody()) &&!(mapObjectAABB.lowerBound.x < footSensorAABB.lowerBound.x && footSensorAABB.upperBound.x < mapObjectAABB.upperBound.x) && mapObjectAABB.upperBound.y - footSensorAABB.upperBound.y > ((20*1.0f)/32)))
//    {
//        return true;
//        
//    }
//    
//    return false;
    
    b2AABB footSensorAABB = Util::getFixtureBoundingBoxDynamic(this->footSensor);
    b2AABB mapObjectAABB = Util::getBodyBoundingBoxDynamic(mapObject->getBody());
    
    if( this->body->GetLinearVelocity().y > 3 || Util::bodiesArePassingThrough(mapObject->getBody(), this->body) || (!Util::bodiesAreTouchingFixture( mapObject->getBody(), this->footSensor) &&!(mapObjectAABB.lowerBound.x < footSensorAABB.lowerBound.x && footSensorAABB.upperBound.x < mapObjectAABB.upperBound.x) && mapObjectAABB.upperBound.y - footSensorAABB.upperBound.y > ((20*1.0f)/32)))
    {
        return true;
        
    }
    
    return false;

}

void Character::stopMove()
{
    this->body->SetLinearVelocity(b2Vec2(0, this->getBody()->GetLinearVelocity().y));
}

void Character::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
    if(holderData->Data == this)
    {
//        PhysicData* physicData = NULL;
//        if(isSideA)
//        {
//            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//        }
//        else
//        {
//            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//        }
//        CCLOG("");
        switch (holderData->BodyId)
        {
            case CHARACTER_FOOT_SENSOR:
            {
                if(collisionData!=NULL)
                {
                    switch (collisionData->BodyId) {
                        case MAP_BASE:
                        {
                            GameObject* mapObject = (GameObject*)collisionData->Data;
                            if(!Util::bodiesArePassingThrough(mapObject->getBody(), this->body))
                            {
                                this->landing ++;
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
                
                if(collisionData!=NULL)
                {
                    
                    switch (collisionData->BodyId) {
                        case MAP_BASE:
                        {
                            MapObject* mapObject = (MapObject*)collisionData->Data;
                            if (!Util::bodiesArePassingThrough(this->body, mapObject->getBody())) {
                                this->isLanding = true;
                            }
                            
                            if(landing == 0 && !Util::bodiesArePassingThrough(this->body, mapObject->getBody()) && Util::bodiesAreTouchingFixture( mapObject->getBody(), this->footSensor))
                            {
                                landing++;
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

void Character::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(holderData->Data == this)
    {
//        PhysicData* physicData = NULL;
//        if(isSideA)
//        {
//            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//        }
//        else
//        {
//            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//        }
        
        switch (holderData->BodyId) {
            case CHARACTER_FOOT_SENSOR:
            {
                if(collisionData!=NULL)
                {
                    switch (collisionData->BodyId) {
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
//                PhysicData* physicData = NULL;
//                if(isSideA)
//                {
//                    physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//                }
//                else
//                {
//                    physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//                }
                
                if(collisionData != NULL)
                {
                    switch (collisionData->BodyId) {
                            
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

void Character::setPhysicGroup(uint16 group)
{
//    for (b2Fixture* f = this->footSensor->GetFixtureList(); f; f = f->GetNext())
//    {
//        if(f != NULL)
//        {
            Util::setFixtureGroup(this->footSensor, GROUP_SENSOR);
//        }
//    }

    
    if(this->normalAttack != NULL)
    {
        this->normalAttack->setPhysicGroup(GROUP_SKILL_DEFAULT);
    }
    
    if(this->skill1 != NULL)
    {
        this->skill1->setPhysicGroup(GROUP_SKILL_DEFAULT);
    }
    
    if(this->skill2 != NULL)
    {
        this->skill2->setPhysicGroup(GROUP_SKILL_DEFAULT);
    }
    
    
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            Util::setFixtureGroup(f, group);
            
            if(f->GetNext() != NULL)
            {
                b2Filter filter = f->GetFilterData();
                filter.maskBits = filter.maskBits ^ GROUP_SKILL_DEFAULT ^ GROUP_MONSTER_SENSOR ^ GROUP_ITEM;
                f->SetFilterData(filter);
            }
        }
    }
}

void Character::notifyByEffect(CCObject* effect)
{
    
    this->characterData.applyEffect((Effect*)effect, this);
    
    HealthPointEffect* gameEffect = HealthPointEffect::create();
    gameEffect->setHealthPoint(((Effect*)effect)->getHealth());
    EffectManager::getInstance()->runEffect(gameEffect, this->getPositionInPixel());
    
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->notifyChange();
    }
}

void Character::removeEffect(CCObject* object)
{
    GameObject::removeEffect(object);
    if(this->listEffect->count() ==0)
    {
        this->characterData.setData(this->originCharacterData);
    }
}

bool Character::isDead()
{
    if(this->characterData.getHealth()<=0)
    {
        return true;
    }
    return false;
}

void Character::destroy()
{
    this->state->onExitState();
    
    if(normalAttack)
    {
        normalAttack->destroy();
    }
    
    if(skill1)
    {
        skill1->destroy();
    }

    if(skill2)
    {
        skill2->destroy();
    }
    GameObject::destroy();
}

void Character::attach(Observer* observer)
{
//    CCLOG("character attach %d",this->listObserver.size());  
    GameObject::attach(observer);
}

void Character::detach(Observer* observer)
{
//    CCLOG("character detach %d",this->listObserver.size());
//    CCLOG("detach - %d", this->listObserver.size());
    GameObject::detach(observer);
    
}
void Character::notifyToDestroy()
{
    CCLOG("character notify destroy");
    GameObject::notifyToDestroy();
}

