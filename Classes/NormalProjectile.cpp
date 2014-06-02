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

NormalProjectile::NormalProjectile()
{
    //    this->holder = NULL;
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
    if(holder != NULL && holder->getBody() != NULL)
    {
        this->data = data;
        //        this->holder = holder;
        this->group = holder->getGroup();
        
        //Create body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.angle = ccpToAngle(ccp(0,0));
        bodyDef.fixedRotation=true;
        bodyDef.bullet = true;
        
        this->body = holder->getBody()->GetWorld()->CreateBody(&bodyDef);
        
        gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
        sc->addFixturesToBody(body, data.getProjectileBodyId());
        
        body->SetGravityScale(this->data.getGravityScale());
        //set position
        body->SetTransform(getStartPosition(holder, body), data.getRotateAngle());
        //
        for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
        {
            PhysicData* pData= new PhysicData();
            pData->bodyId = PROJECTILE;
            pData->gameObjectID = PROJECTILE_OBJECT;
            pData->fixtureId = PROJECTILE_FIXTURE;
            pData->data = this;
            f->SetUserData(pData);
        }
        
        //
        this->sprite = CCSprite::create();
        //
        this->data.getAnimation()->getAnimation()->setLoops(INFINITY);
        CCAnimate* action = CCAnimate::create(this->data.getAnimation()->getAnimation());
        this->sprite->runAction(action);
        //
        holder->getSprite()->getParent()->addChild(this->sprite, this->data.getAnimationLayerIndex());
        //
        if(holder->getDirection() == LEFT)
        {
            this->flipDirection(LEFT);
            this->body->SetLinearVelocity(b2Vec2(-this->data.getSpeedX(), this->data.getSpeedY()));
        }
        else if(holder->getDirection() == RIGHT)
        {
            this->flipDirection(RIGHT);
            this->body->SetLinearVelocity(b2Vec2(this->data.getSpeedX(), this->data.getSpeedY()));
        }
        //schedule life time
        this->lifeTimeScheduled = ScheduleManager::getInstance()->scheduleForGameObject(this, this->data.getLifeTime());
        this->lifeTimeScheduled->retain();
        //
    }
    else
    {
        GameObjectManager::getInstance()->addObjectRemoved(this);
        GameObjectManager::getInstance()->removeGameObject(this);
    }
}

NormalProjectile::~NormalProjectile()
{
    if(body!=NULL)
    {
        this->body->SetActive(false);
    }
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
    b2Vec2 anchorA = getGlobalBodyStartPosition(holder->getBody(), tempA);
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

b2Vec2 NormalProjectile::getGlobalBodyStartPosition(b2Body* body, JointDef jointDef)
{
    if(body == NULL)
    {
        return b2Vec2(0,0);
    }
    
    //set joint anchor A
    b2AABB boundingBox = Util::getBodyBoundingBoxDynamic(body);
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

void NormalProjectile::update(float dt)
{
    if(this->sprite != NULL)
    {
        CCPoint bodyPosition = ccp(this->body->GetPosition().x*PTM_RATIO,this->body->GetPosition().y*PTM_RATIO);
        this->sprite->setPosition(bodyPosition);
        //        this->sprite->setVisible(false);
        this->sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body->GetAngle()));
    }
}


void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(collisionData == NULL /*|| otherData->Data == this->holder*/)
    {
        return;
    }
    //
    switch (collisionData->bodyId)
    {
        case CHARACTER_BODY:
        {
            Character* character = (Character*)collisionData->data;
            if(character != NULL /*&& character != holder*/)
            {
                if(character->getGroup() == /*this->holder->getGroup()*/this->group)
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
                        remove();
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

void NormalProjectile::remove()
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
    GameObjectManager::getInstance()->removeGameObject(this);
}

void NormalProjectile::excuteScheduledFunction(CCObject* pSender, void *object)
{
    if(object != NULL)
    {
        if(this->lifeTimeScheduled != NULL)
        {
            this->lifeTimeScheduled->release();
            this->lifeTimeScheduled = NULL;
        }
        
        GameObjectManager::getInstance()->addObjectRemoved((GameObject*)object);
        GameObjectManager::getInstance()->removeGameObject(this);
    }
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

