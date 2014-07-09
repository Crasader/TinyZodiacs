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
#include "Affect.h"
#include "HealthPointEffect.h"
#include "EffectManager.h"
#include "AnimationEffect.h"

USING_NS_CC;

Character::Character()
{
    this->state = NULL;
    this->landing = 0;
    this->currentJumpCount = 0;
    this->isDead = false;
    
    this->listSkill = CCArray::create();
    this->listSkill->retain();
    
    runAnimation = NULL;
    jumpAnimation = NULL;
    attackAnimation = NULL;
    idleAnimation = NULL;
    flyAnimation = NULL;
    fallAnimation = NULL;
    dieAnimation = NULL;
    skill1Animation = NULL;
    skill2Animation = NULL;
    
    playedHurtSoundId =-1;
    playedDeathSoundId =-1;
    playedJumpSoundId=-1;
}

Character::~Character()
{
    //    this->footSensor->GetWorld()->DestroyBody(this->footSensor);
    this->listSkill->removeAllObjects();
    this->listSkill->release();
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
            scharacterData->bodyId = CHARACTER_BODY;
            scharacterData->data = this;
            scharacterData->gameObjectID = this->gameObjectID;
            
            if(f->GetNext() != NULL)
            {
                scharacterData->fixtureId = BODY_SUB_FIXTURE;
            }
            else
            {
                scharacterData->fixtureId = BODY_MAIN_FIXTURE;
            }
            f->SetUserData(scharacterData);
        }
    }
    //create foot sensor
    createFootSensor();
    
    //    this->body->SetType(b2_kinematicBody);
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
    if(this->isDead == false)
    {
        GameObject::update(dt);
        this->state->update(dt);
        
        CCObject* skill;
        CCARRAY_FOREACH(this->listSkill, skill)
        {
            ((AbstractSkill*)skill)->update(dt);
        }
        
        if(this->body->GetLinearVelocity().x >=2)
        {
            flipDirection(RIGHT);
        }
        else if(this->body->GetLinearVelocity().x <=-2)
        {
            flipDirection(LEFT);
        }
        
        if(checkDead() == true)
        {
            die();
        }
        
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
            //
            playSoundByState(JUMP_SOUND);
            //
            changeState(new CharacterJumpState(this));
            
            b2Vec2 vel = this->body->GetLinearVelocity();
            vel.y = force;
            this->body->SetLinearVelocity( vel );
            
            this->currentJumpCount++;
        }
    }
    
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
    sensorData->bodyId = CHARACTER_BODY;
    sensorData->data = this;
    sensorData->gameObjectID = this->gameObjectID;
    sensorData->fixtureId = FOOT_SENSOR_FIXTURE;
    fixDef.userData = sensorData;
    
    this->footSensor = this->body->CreateFixture(&fixDef);
}

bool Character::isCharacterCanPassThoughMapObject(MapObject* mapObject)
{
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
    GameObject::checkCollisionDataInBeginContact(holderData, collisionData, contact);
    if(holderData->data == this)
    {
        switch (holderData->fixtureId)
        {
            case FOOT_SENSOR_FIXTURE:
            {
                if(collisionData!=NULL)
                {
                    switch (collisionData->gameObjectID) {
                        case WALL:
                        {
                            Wall* deathWall= static_cast<Wall*>(collisionData->data);
                    
                            
                            if(deathWall != NULL && deathWall->getDeadWall() == true)
                            {
                                die();
                            }
                        }
                            break;
                            
                        default:
                            break;
                    }
                    
                    
                    switch (collisionData->bodyId) {
                        case MAP_BASE:
                        {
                            GameObject* mapObject = (GameObject*)collisionData->data;
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
            case BODY_MAIN_FIXTURE:
            {
                
                if(collisionData!=NULL)
                {
                    
                    switch (collisionData->bodyId) {
                        case MAP_BASE:
                        {
                            MapObject* mapObject = (MapObject*)collisionData->data;
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
    if(holderData->data == this)
    {
        switch (holderData->fixtureId) {
            case FOOT_SENSOR_FIXTURE:
            {
                if(collisionData!=NULL)
                {
                    switch (collisionData->bodyId) {
                        case MAP_BASE:
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
                
                break;
                
            case BODY_MAIN_FIXTURE:
            {
                if(collisionData != NULL)
                {
                    switch (collisionData->bodyId) {
                            
                        case MAP_BASE:
                        {
                            //  this->body->GetWorld()->ClearForces();
                            //                            if (!Util::bodiesArePassingThrough(this->body, mapObject->getBody())) {
                            //                                this->isLanding = true;
                            //                            }
                        }
                            break;
                        case WALL_BODY:
                            if(this->body->GetLinearVelocity().y > 2)
                            {
                                this->body->SetLinearVelocity(b2Vec2(0,5));
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
    Util::setFixtureGroup(this->footSensor, GROUP_SENSOR);
    
    CCObject* skill;
    CCARRAY_FOREACH(this->listSkill, skill)
    {
        ((AbstractSkill*)skill)->setPhysicGroup(GROUP_SKILL_DEFAULT);
    }
    
    b2Fixture* fixture = this->body->GetFixtureList();
    Util::setFixtureGroup(fixture, group);
    
    for (b2Fixture* f = fixture->GetNext(); f; f = f->GetNext())
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

void Character::notifyByAffect(Affect* affect)
{
    if(this->isDestroyed == false)
    {
        float oldHp = this->characterData.getHealth();
//        this->characterData.applyAffect((Affect*)affect, this);
        calculateCharacterDataOnNotify((Affect*)affect);
        
        if(this->gameObjectView != NULL)
        {
            this->gameObjectView->notifyChange();
        }
        
        
        if(this->characterData.getHealth()-oldHp == 0)
        {
        }
        else
        {
            HealthPointEffect* effect = HealthPointEffect::create();
            effect->setHealthPoint(this->characterData.getHealth()-oldHp);
            EffectManager::getInstance()->runEffect(effect, this->getPositionInPixel(),ABOVE_CHARACTER_LAYER);
        }
        if(this->characterData.getHealth()-oldHp<0)
        {
            if(this->getIsDead() == true)
            {
                playSoundByState(DEATH_SOUND);
            }
            else
            {
                playSoundByState(HURT_SOUND);
            }
        }
        //play sound
        playSFX(affect->getSoundEffect().c_str());
    }
}

void Character::removeAffect(Affect* affect)
{
    GameObject::removeAffect(affect);
//    if(this->listAffect->count() ==0)
//    {
//        this->characterData.setData(this->originCharacterData);
//    }
    calculateCharacterDataOnDetach();
}
void Character::calculateCharacterDataOnDetach()
{
    if(this->listAffect != NULL)
    {
        CCObject* affectObj;
        
        CharacterData tempData = CharacterData::getRawData();
        CCARRAY_FOREACH(this->listAffect, affectObj)
        {
            Affect* affect = (Affect*)affectObj;
            tempData.setAttack(tempData.getAttack() + affect->getAttack());
            tempData.setAttackSpeed(tempData.getAttackSpeed() + affect->getAttackSpeed());
            tempData.setDefense(tempData.getDefense() + affect->getDefense());
//            tempData.setHealth(tempData.getHealth() + affect->getHealth());
            tempData.setJumpHeight(tempData.getJumpHeight() + affect->getJumpHeight());
            tempData.setMaxJumpTimes(tempData.getMaxJumpTimes() + affect->getMaxJump());
            tempData.setSpeed(tempData.getSpeed() + affect->getSpeed());
        }
        //caculate with original
        tempData.setAttack(tempData.getAttack() + this->originCharacterData.getAttack());
        tempData.setAttackSpeed(tempData.getAttackSpeed() + this->originCharacterData.getAttackSpeed());
        tempData.setDefense(tempData.getDefense() + this->originCharacterData.getDefense());
        tempData.setJumpHeight(tempData.getJumpHeight() + this->originCharacterData.getJumpHeight());
        tempData.setMaxJumpTimes(tempData.getMaxJumpTimes() + this->originCharacterData.getMaxJumpTimes());
        tempData.setSpeed(tempData.getSpeed() + this->originCharacterData.getSpeed());
        //
        this->characterData.applyData(tempData,this->originCharacterData);
//        CCLOG("Detach Affect count %d", this->listAffect->count());
    }
}

void Character::calculateCharacterDataOnNotify(Affect* mAffect)
{
    if(this->listAffect != NULL)
    {
        CCObject* affectObj;
        
        CharacterData tempData = CharacterData::getRawData();
        CCARRAY_FOREACH(this->listAffect, affectObj)
        {
            Affect* affect = (Affect*)affectObj;
            tempData.setAttack(tempData.getAttack() + affect->getAttack());
            tempData.setAttackSpeed(tempData.getAttackSpeed() + affect->getAttackSpeed());
            tempData.setDefense(tempData.getDefense() + affect->getDefense());
            tempData.setJumpHeight(tempData.getJumpHeight() + affect->getJumpHeight());
            tempData.setMaxJumpTimes(tempData.getMaxJumpTimes() + affect->getMaxJump());
            tempData.setSpeed(tempData.getSpeed() + affect->getSpeed());
            
            if(mAffect != NULL && affect == mAffect)
            {
                float critRatio=1;
                if(Util::randomIntInRange(0, 100)<= affect->getCritChance())
                {
                    critRatio = affect->getCritRatio();
                }
                
                tempData.setHealth(tempData.getHealth() + affect->getHealth()*critRatio);
            }
        }
        //caculate with original
        tempData.setAttack(tempData.getAttack() + this->originCharacterData.getAttack());
        tempData.setAttackSpeed(tempData.getAttackSpeed() + this->originCharacterData.getAttackSpeed());
        tempData.setDefense(tempData.getDefense() + this->originCharacterData.getDefense());
        tempData.setJumpHeight(tempData.getJumpHeight() + this->originCharacterData.getJumpHeight());
        tempData.setMaxJumpTimes(tempData.getMaxJumpTimes() + this->originCharacterData.getMaxJumpTimes());
        tempData.setSpeed(tempData.getSpeed() + this->originCharacterData.getSpeed());
        //
        this->characterData.applyData(tempData,this->originCharacterData);
//        CCLOG("Notifi Affect count %d", this->listAffect->count());
    }
}

bool Character::checkDead()
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
    
    CCObject* skill;
    CCARRAY_FOREACH(this->listSkill, skill)
    {
        ((AbstractSkill*)skill)->destroy();
    }
    GameObject::destroy();
}

void Character::die()
{
    CCObject* skill;
    CCARRAY_FOREACH(this->listSkill, skill)
    {
//        ((AbstractSkill*)skill)->stopImmediately();
        ((AbstractSkill*)skill)->stopSkillSafely();
    }
    //
    //    playSoundByState(DEATH_SOUND);
    //
    this->isDead = true;
    changeState(new CharacterDieState(this));
    
    cleanAllAffect();
    
}

void Character::attach(Observer* observer)
{
    GameObject::attach(observer);
}

void Character::detach(Observer* observer)
{
    GameObject::detach(observer);
}

void Character::notifyToDestroy()
{
    GameObject::notifyToDestroy();
}

void Character::playSoundByState(CharacterSound characterSoundState)
{
    switch (characterSoundState) {
        case DEATH_SOUND:
            playSFX(this->getSoundData().getDeathSoundStr().c_str());
            break;
        case HURT_SOUND:
            playSFX(this->getSoundData().getHurtSoundStr().c_str());
            break;
        case JUMP_SOUND:
            playSFX(this->getSoundData().getJumpSoundStr().c_str());
            break;
        default:
            break;
    }
}

void Character::setSkill(CharacterSkill skillIndex, AbstractSkill* skill)
{
    if(skill == NULL)
    {
//        CCLOG("skill null");
        //    assert(0);
        return;
    }
    if(skillIndex >= this->listSkill->count())
    {
        this->listSkill->addObject(skill);
    }
    else
    {
        this->listSkill->insertObject(skill, skillIndex);
    }
}

void Character::playSkill(CharacterSkill skillIndex, AnimationObject* characterAnimation)
{
    AbstractSkill* skill = getSkill(skillIndex);
    if(skill == NULL)
    {
        assert(0);
    }
    if(skill != NULL && skill->getIsExcutable() && this->state->attack() && isDead == false)
    {
        
        changeState(new CharacterAttackState(this,skill,characterAnimation));
    }
}

AbstractSkill* Character::getSkill(CharacterSkill skillIndex)
{
    if(skillIndex >= this->listSkill->count())
    {
        
        return NULL;
    }
    AbstractSkill* skill = (AbstractSkill*)this->listSkill->objectAtIndex(skillIndex);
    
    return skill;
}

void Character::playSkill(CharacterSkill skillIndex)
{
    AnimationObject* correctAnimation;
    switch (skillIndex) {
        case NORMAL_ATTACK:
            correctAnimation = this->attackAnimation;
            break;
        case SKILL_1:
            correctAnimation = this->skill1Animation;
            break;
        case SKILL_2:
            correctAnimation = this->skill2Animation;
            break;
        default:
            correctAnimation = this->attackAnimation;
            break;
    }
    playSkill(skillIndex, correctAnimation);
}

bool Character::isBodyFixture(FixtureID fixtureId)
{
    if(fixtureId == BODY_MAIN_FIXTURE || fixtureId == BODY_SUB_FIXTURE)
    {
        return true;
    }
    return false;
}

void Character::checkCollisionDataInPreSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2Manifold* oldManifold)
{

}

void Character::checkCollisionDataInPostSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2ContactImpulse* impulse)
{
    if(holderData->data == this)
    {
        switch (holderData->fixtureId)
        {
            case BODY_MAIN_FIXTURE:
            {
                
                if(collisionData!=NULL)
                {
                    
                    switch (collisionData->bodyId) {
                        case MAP_BASE:
                        {
                            
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