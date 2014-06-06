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

NormalProjectile::NormalProjectile()
{
    this->lifeTimeScheduled = NULL;
    this->group = NEUTRAL;
}

bool NormalProjectile::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    return true;
}

void NormalProjectile::setData(NormalShootingSkillData data, GameObject* holder)
{

    this->data = data;
    this->group = holder->getGroup();
    this->holderSpeed = holder->getBody()->GetLinearVelocity();
    
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=false;
    bodyDef.bullet = true;
    
    this->body = GameManager::getInstance()->getGameplayHolder().worldHolder->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, data.getProjectileBodyId());
    
    body->SetGravityScale(this->data.getGravityScale());
    //set position
    body->SetTransform(getStartPosition(holder, body), data.getRotateAngle());
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
    
    // set direction
    if(holder->getDirection() == LEFT)
    {
        this->flipDirection(LEFT);
    }
    else if(holder->getDirection() == RIGHT)
    {
        this->flipDirection(RIGHT);
    }
    
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(NormalProjectile::destroy));
    this->lifeTimeScheduled = ScheduleManager::getInstance()->scheduleFunction(destroyFunction, NULL, this->data.getLifeTime(), 1);
    this->lifeTimeScheduled->retain();
    //Allow rotate
    // Sprite
    this->sprite = CCSprite::create();
    GameManager::getInstance()->getGameplayHolder().nodeHolder->addChild(this->sprite, this->data.getAnimationLayerIndex());

}

NormalProjectile::~NormalProjectile()
{
  
}

b2Vec2 NormalProjectile::getStartPosition(GameObject* holder, b2Body* me)
{
    //
    int holder_join_type = JOINT_CENTER;
    int this_join_type = JOINT_CENTER;
    if(this->data.getJointDefA().x == JOINT_REAR)
    {
        if(holder->getDirection() == LEFT)
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
    b2AABB thisBoudningBox = Util::getBodyBoundingBoxDynamic(body);
    if(this->data.getJointDefA().x == JOINT_REAR && this->data.getJointDefB().x == JOINT_REAR)
    {
        if(holder->getDirection() == LEFT)
        {
            anchorA.x -= this->data.getJointDefB().offsetX;
            anchorA.x -= abs(thisBoudningBox.upperBound.x);
        }
        else if(holder->getDirection() == RIGHT)
        {
            anchorA.x += this->data.getJointDefB().offsetX;
            anchorA.x += abs(thisBoudningBox.lowerBound.x);
        }
    }
    
    return anchorA;
}

b2Vec2 NormalProjectile::getGlobalBodyStartPosition(GameObject* holder, JointDef jointDef)
{
    if(body == NULL)
    {
        return b2Vec2(0,0);
    }
    
    //set joint anchor A
    b2AABB boundingBox = Util::getGameObjectBoundingBoxDynamic(holder);

//    b2Fixture* mainFix = Util::getFixtureById(body, BODY_MAIN_FIXTURE);
//    b2AABB boundingBoxMain = Util::getFixtureBoundingBoxDynamic(mainFix);
    
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
    if(this->direction == LEFT)
    {
        this->body->SetLinearVelocity(b2Vec2(-this->data.getSpeedX(), this->data.getSpeedY()));
    }
    else if(this->direction == RIGHT)
    {
        this->body->SetLinearVelocity(b2Vec2(this->data.getSpeedX(), this->data.getSpeedY()));
    }
    this->data.getAnimation()->getAnimation()->setLoops(INFINITY);
    CCAnimate* action = CCAnimate::create(this->data.getAnimation()->getAnimation());
    this->sprite->runAction(action);
    
    GameObjectManager::getInstance()->addGameObject(this);
}

void NormalProjectile::update(float dt)
{
    this->body->SetTransform(this->body->GetPosition(),atan2(this->body->GetLinearVelocity().y,this->body->GetLinearVelocity().x)-3.14);
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
                if(character->getGroup() == this->group)
                {
                    // CCLOG("Allie begin");
                }
                else
                {
                    // CCLOG("Enemy begin");
                    for(int i=0 ; i<this->data.getListEnemyEffect().size() ; i++)
                    {
                        Affect* affect = Affect::create();
                        affect->setData(this->data.getListEnemyEffect()[i]);
                        affect->setHolder(character);
                        character->applyAffect(affect);
                    }
                    
                    if(this->data.getPiercing() == false)
                    {
                        destroy();
                    }
                }
            }
        }
        default:
            break;
    }
}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
}

void NormalProjectile::destroy()
{
    if(this->lifeTimeScheduled != NULL)
    {
        if(this->lifeTimeScheduled->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(this->lifeTimeScheduled);
        }
        this->lifeTimeScheduled->release();
        this->lifeTimeScheduled= NULL;
    }
    
    GameObjectManager::getInstance()->addObjectRemoved(this);
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
                if(this->data.getTerrainCollide() == true)
                {
                    b2Filter filter = f->GetFilterData();
                    filter.maskBits = filter.maskBits | GROUP_TERRAIN;
                    f->SetFilterData(filter);
                }
            }
        }
    }
}

