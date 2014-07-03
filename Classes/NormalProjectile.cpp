//
//  NormalProjectile.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/20/14.
//
//

#include "NormalProjectile.h"
#include "NormalShootingSkillData.h"
#include "GB2ShapeCache-x.h"
#include "Util.h"
#include "LayerIndexConstants.h"
#include "Character.h"
#include "GameObjectManager.h"
#include "ScheduleManager.h"
#include "Affect.h"
#include "EffectData.h"
#include "GameManager.h"
#include "AnimationObject.h"
#include "EffectManager.h"
#include "PhysicConstants.h"


NormalProjectile::NormalProjectile()
{
    this->gameObjectID = PROJECTILE_OBJECT;
    this->lifeTimeScheduled = NULL;
    this->timeTickAction = NULL;
    this->group = NEUTRAL;
    this->listTarget = NULL;
    this->isDisable=false;
}

NormalProjectile::~NormalProjectile()
{
}

bool NormalProjectile::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    return true;
}

void NormalProjectile::setData(NormalShootingSkillData data, GameObjectCalculateData holder)
{
    
    this->data = data;
    this->group = holder.getGroup();
    this->holderSpeed = holder.getSpeed();
    
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=false;
    bodyDef.bullet = true;
    
    this->body = GameManager::getInstance()->getGameplayHolder().worldHolder->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, data.getProjectileData().getProjectileBodyId());
    
    body->SetGravityScale(this->data.getProjectileData().getGravityScale());
    //set position
    float32 bodyAngle = body->GetAngle();
    body->SetTransform(getStartPosition(holder, body), bodyAngle);
    //
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        PhysicData* pData = new PhysicData();
        pData->bodyId = PROJECTILE;
        pData->gameObjectID = PROJECTILE_OBJECT;
        pData->fixtureId = PROJECTILE_FIXTURE;
        pData->data = this;
        f->SetUserData(pData);
    }
    //
    if(data.getApplyType() == APPLY_OVERTIME)
    {
        this->listTarget = CCArray::create();
        this->listTarget->retain();
    }
    else
    {
        this->listTarget = NULL;
    }
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(NormalProjectile::destroy));
    this->lifeTimeScheduled = ScheduleManager::getInstance()->scheduleFunction(destroyFunction, NULL, this->data.getLifeTime(), 1);
    this->lifeTimeScheduled->retain();
    // Sprite
    this->sprite = CCSprite::create();
    GameManager::getInstance()->getGameplayHolder().nodeHolder->addChild(this->sprite, this->data.getProjectileData().getStateAnimation().getAnimationLayerIndex());
    // set direction
    if(holder.getDirection() == LEFT)
    {
        this->flipDirection(LEFT);
        this->sprite->setFlipX(true);
    }
    else if(holder.getDirection() == RIGHT)
    {
        this->flipDirection(RIGHT);
        this->sprite->setFlipX(false);
    }
}

b2Vec2 NormalProjectile::getStartPosition(GameObjectCalculateData holder, b2Body* me)
{
    //
    int holder_join_type = JOINT_CENTER;
    int this_join_type = JOINT_CENTER;
    if(this->data.getJointDefA().x == JOINT_REAR)
    {
        if(holder.getDirection() == LEFT)
        {
            holder_join_type = JOINT_BOTTOM_OR_LEFT;
        }
        else
        {
            holder_join_type = JOINT_TOP_OR_RIGHT;
        }
        if(this->data.getJointDefB().x == JOINT_REAR)
        {
            this_join_type = -holder_join_type;
        }
    }
    //Get holder start position
    //create joint
    JointDef tempA = data.getJointDefA();
    tempA.x = holder_join_type;
    b2Vec2 anchorA = getGlobalBodyStartPosition(holder, tempA);
    
    JointDef tempB = data.getJointDefB();
    tempB.x = this_join_type;
    b2AABB thisBoudningBox = Util::getBodyBoundingBox(body);
    //
    switch (tempB.x) {
        case JOINT_CENTER:
            anchorA.x -= 0+tempB.offsetX;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            anchorA.x -= thisBoudningBox.lowerBound.x - tempB.offsetX;
            break;
        case JOINT_TOP_OR_RIGHT:
            anchorA.x -= thisBoudningBox.upperBound.x + tempB.offsetX;
            break;
        default:
            break;
    }
    
    switch (tempB.y) {
        case JOINT_CENTER:
            anchorA.y -= tempB.offsetY;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            anchorA.y -= thisBoudningBox.lowerBound.y - tempB.offsetY;
            break;
        case JOINT_TOP_OR_RIGHT:
            anchorA.y -= thisBoudningBox.upperBound.y + tempB.offsetY;
            break;
        default:
            break;
    }
    //
    if(this->data.getJointDefA().x == JOINT_REAR /*&& this->data.getJointDefB().x == JOINT_REAR*/)
    {
        if(holder.getDirection() == LEFT)
        {
            anchorA.x -= this->data.getPositionPlusPerUnit().x;
            anchorA.y += this->data.getPositionPlusPerUnit().y;
        }
        else if(holder.getDirection() == RIGHT)
        {
            anchorA.x += this->data.getPositionPlusPerUnit().x;
            anchorA.y += this->data.getPositionPlusPerUnit().y;
        }
    }
    
    return anchorA;
}

b2Vec2 NormalProjectile::getGlobalBodyStartPosition(GameObjectCalculateData holder, JointDef jointDef)
{
    if(body == NULL)
    {
        return b2Vec2(0,0);
    }
    //set joint anchor A
    b2AABB boundingBox = holder.getbodyBoundingBoxDynamic();
    
    b2Vec2 jointAAnchor(0,0);
    switch (jointDef.x) {
        case JOINT_CENTER:
            jointAAnchor.x = (boundingBox.lowerBound.x+boundingBox.upperBound.x)/2+jointDef.offsetX;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.x = boundingBox.lowerBound.x - jointDef.offsetX;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.x = boundingBox.upperBound.x + jointDef.offsetX;
            break;
        default:
            break;
    }
    
    switch (jointDef.y) {
        case JOINT_CENTER:
            jointAAnchor.y = (boundingBox.lowerBound.y+boundingBox.upperBound.y)/2+jointDef.offsetY;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.y = boundingBox.lowerBound.y - jointDef.offsetY;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.y = boundingBox.upperBound.y + jointDef.offsetY;
            break;
        default:
            break;
    }
    
    return jointAAnchor;
}

void NormalProjectile::shoot()
{
    float forceX = -(cos(this->data.getAngle()))*this->data.getSpeed()/*+this->holderSpeed.x*/;
    float forceY = -sin(this->data.getAngle())*this->data.getSpeed();
    if(this->direction == LEFT)
    {
        
    }
    else if(this->direction == RIGHT)
    {
        forceX = -forceX;
        forceY = -forceY;
    }
    this->body->SetLinearVelocity(b2Vec2(forceX, forceY));
    
    //if(data.getLifeTime() >0 && data.getTimeTick() >0)
    if(data.getApplyType() == APPLY_OVERTIME)
    {
        CCCallFunc* timeTick = CCCallFunc::create(this, callfunc_selector(NormalProjectile::applyEffectOnTimeTick));
        this->timeTickAction = ScheduleManager::getInstance()->scheduleFunctionForever(timeTick, NULL, this->data.getTimeTick());
        this->timeTickAction->retain();
    }
    //
    GameObjectManager::getInstance()->addGameObject(this);
}

void NormalProjectile::update(float dt)
{
    switch (this->data.getAngleType()) {
        case FREE_STYLE:
        {
            float rotateAngle = atan2(this->body->GetLinearVelocity().y,this->body->GetLinearVelocity().x);
            this->body->SetTransform(this->body->GetPosition(),rotateAngle-3.14);
        }
            break;
        case HOLDER_DIRECTION:
        {
//            flipDirection(RIGHT);
        }
            break;
        default:
            break;
    }
    GameObject::update(dt);
}

void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(collisionData == NULL)
    {
        return;
    }
    //
    switch (collisionData->bodyId)
    {
        case CHARACTER_BODY:
        {
            Character* character = (Character*)collisionData->data;
            if(character != NULL)
            {
                bool shouldHaveEffect = false;
                if(character->getGroup() == this->group)
                {
                    Util::applyEffectFromList(data.getListAlliesEffect(), character);
                    if(data.getListAlliesEffect().size()>0)
                    {
                        shouldHaveEffect=true;
                    }
                }
                else
                {
                    Util::applyEffectFromList(data.getListEnemyEffect(), character);
                    if(data.getListEnemyEffect().size()>0)
                    {
                        shouldHaveEffect=true;
                    }
                }
                //
                if(data.getApplyType() == APPLY_OVERTIME)
                {
                    if(listTarget!= NULL && listTarget->indexOfObject(character) == CC_INVALID_INDEX)
                    {
                        listTarget->addObject(character);
                        character->attach(this);
                    }
                }
                //
                if(shouldHaveEffect)
                {
                    if(this->data.getProjectileData().getStateAnimation().getHitStateAnimationID() != "")
                    {
                        bool shouldFlip=false;
                        if(this->getDirection() == LEFT)
                        {
                            shouldFlip = false;
                        }
                        else
                        {
                            shouldFlip = true;
                        }
        
                        AnimationEffect* hitEffect = AnimationEffect::create();
                        hitEffect->setAnimation(this->data.getProjectileData().getStateAnimation().getHitStateAnimationID().c_str(),shouldFlip);
                        EffectManager::getInstance()->runEffect(hitEffect, this->getPositionInPixel(),this->data.getProjectileData().getStateAnimation().getAnimationLayerIndex());
                        //
                        playSoundByState(HIT_SOUND);
                    }
                    
                    if(shouldDestroy())
                    {
                        this->destroy();
                    }
                }
            }
        }
            break;
        case MAP_BASE:
        {
            if(this->data.getProjectileData().getTerrainCollide() == true)
            {
                this->destroy();
            }
        }
            break;
        default:
            break;
    }
}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(collisionData == NULL)
    {
        return;
    }
    //
    switch (collisionData->bodyId)
    {
        case CHARACTER_BODY:
        {
            Character* character = (Character*)collisionData->data;
            if(character != NULL)
            {
                if(listTarget != NULL)
                {
                    if(this->listTarget->indexOfObject(character) != CC_INVALID_INDEX )
                    {
                        character->detach(this);
                        listTarget->removeObject(character);
                    }
                }
            }
        }
            break;
        case MAP_BASE:
        {
        }
            break;
        default:
            break;
    }
}

void NormalProjectile::destroy()
{
    this->isDisable = true;
    //
//    this->body->SetActive(false);
    //stop time tick
    if(this->timeTickAction != NULL)
    {
        if(this->timeTickAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(this->timeTickAction);
        }
        this->timeTickAction->release();
        this->timeTickAction = NULL;
    }
    //
    if(this->lifeTimeScheduled != NULL)
    {
        if(this->lifeTimeScheduled->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(this->lifeTimeScheduled);
        }
        this->lifeTimeScheduled->release();
        this->lifeTimeScheduled= NULL;
    }
    //
    if(this->listTarget != NULL)
    {
        CCObject* object = NULL;
        CCARRAY_FOREACH(this->listTarget, object)
        {
            Character* gameObject = static_cast<Character*>(object);
            gameObject->detach(this);
        }
        this->listTarget->removeAllObjects();
        this->listTarget = NULL;
    }
    //
    if(this->data.getProjectileData().getStateAnimation().getHitStateAnimationID() != "")
    {
        bool shouldFlip=false;
        if(this->getDirection() == LEFT)
        {
            shouldFlip = false;
        }
        else
        {
            shouldFlip = true;
        }

        AnimationEffect* hitEffect = AnimationEffect::create();
        hitEffect->setAnimation(this->data.getProjectileData().getStateAnimation().getHitStateAnimationID().c_str(),shouldFlip);
        EffectManager::getInstance()->runEffect(hitEffect, this->getPositionInPixel(),this->data.getProjectileData().getStateAnimation().getAnimationLayerIndex());
    }
    //
    this->sprite->stopAllActions();
    //
    GameObjectManager::getInstance()->addObjectRemoved(this);
    //
    playSoundByState(DIE_SOUND);
}

void NormalProjectile::setGroup(uint16 group)
{
    if(this->body!=NULL)
    {
        for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
        {
            if(f != NULL)
            {
                Util::setFixtureGroup(f, group);
                if(this->data.getProjectileData().getTerrainCollide() == true)
                {
                    b2Filter filter = f->GetFilterData();
                    filter.maskBits = filter.maskBits | GROUP_TERRAIN;
                    f->SetFilterData(filter);
                }
            }
        }
    }
}

void NormalProjectile::initData(NormalShootingSkillData data, GameObjectCalculateData holder, uint16 group)
{
    //    this->sprite->stopAllActions();
    this->setData(data, holder);
    this->setGroup(group);
}

void NormalProjectile::initDataAndShoot(NormalShootingSkillData data, GameObjectCalculateData holder, uint16 group)
{
    initData(data, holder, group);
    
    CCArray* array = CCArray::create();
    
    if(this->data.getProjectileData().getStateAnimation().getCreatedStateAnimationID() != "")
    {
        AnimationObject* animationObj = DataCollector::getInstance()->getAnimationObjectByKey(this->data.getProjectileData().getStateAnimation().getCreatedStateAnimationID().c_str());
        CCAnimate* animation = CCAnimate::create(animationObj->getAnimation());
        array->addObject(animation);
    }
    //
    playSoundByState(CREATE_SOUND);
    //
    CCCallFunc* action = CCCallFunc::create(this, callfunc_selector(NormalProjectile::changeCreatAnimationToShootingAnimation));
    array->addObject(action);
    CCSequence* sequence = CCSequence::create(array);
    this->sprite->runAction(sequence);
    
    shoot();
}

void NormalProjectile::changeCreatAnimationToShootingAnimation()
{
    AnimationObject* animationObj = DataCollector::getInstance()->getAnimationObjectByKey(this->data.getProjectileData().getStateAnimation().getShootingStateAnimationID().c_str());
    CCAnimate* animation = CCAnimate::create(animationObj->getAnimation());
    this->sprite->runAction(animation);
    //
    playSoundByState(SHOOT_SOUND);
//    shoot();
}

void NormalProjectile::applyEffectOnTimeTick()
{
    if(isDisable)
    {
        return;
    }
    CCObject* obj = NULL;
    CCARRAY_FOREACH(listTarget, obj)
    {
        Character* character = (Character*)obj;
        bool isApplyed = false;
        if(character->getGroup() == this->group)
        {
            Util::applyEffectFromList(this->data.getListAlliesEffect(), character);
            if(this->data.getListAlliesEffect().size()>0)
            {
                isApplyed = true;
            }
        }
        else
        {
            Util::applyEffectFromList(this->data.getListEnemyEffect(), character);
            if(this->data.getListEnemyEffect().size()>0)
            {
                isApplyed = true;
            }
        }
        
        
        if(isApplyed && shouldDestroy())
        {
            destroy();
        }
    }
}

void NormalProjectile::notifyToDestroy(GameObject* object)
{
    if(this->listTarget != NULL)
    {
        if(this->listTarget->indexOfObject(object) != CC_INVALID_INDEX)
        {
            this->listTarget->removeObject(object);
        }
    }
}

bool NormalProjectile::shouldDestroy()
{
    if(this->data.getProjectileData().getPiercing() <=0)
    {
        return true;
    }
    else
    {
        ProjectileData newData = data.getProjectileData();
        newData.setPiercing(newData.getPiercing()-1);
        this->data.setProjectileData(newData);
        return false;
    }
}

void NormalProjectile::playSoundByState(ProjectileSound soundState)
{
    switch (soundState) {
        case CREATE_SOUND:
            playSFX(this->data.getProjectileData().getSoundData().getCreateSoundStr().c_str());
            break;
        case HIT_SOUND:
            playSFX(this->data.getProjectileData().getSoundData().getHitSoundStr().c_str());
            break;
        case SHOOT_SOUND:
//            playSFX(this->data.getProjectileData().getSoundData().getShootSoundStr().c_str());
            break;
        case DIE_SOUND:
            playSFX(this->data.getProjectileData().getSoundData().getDieSoundStr().c_str());
            break;
        default:
            break;
    }
}