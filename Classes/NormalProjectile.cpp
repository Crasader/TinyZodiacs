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
#include "AnimationFactory.h"
#include "Util.h"
#include "LayerIndexConstants.h"

NormalProjectile::NormalProjectile(NormalShootingSkillData data, GameObject* holder)
{
    contact_count=0;
    scheduled = false;
    this->data = data;
    
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
    body->SetTransform(getStartPosition(holder, body), body->GetAngle());
    //
    PhysicData* pData= new PhysicData();
    pData->Id = PROJECTILE;
    pData->Data = this;
    
    body->SetUserData(pData);
    
    //
    this->sprite = CCSprite::create();
    this->sprite->retain();
    
    CCAnimate* action = CCAnimate::create(this->data.getAnimation()->getAnimation());
    this->sprite->runAction(action);
    
    holder->getSprite()->getParent()->addChild(this->sprite, this->data.getAnimationLayerIndex());
    //
//    if(holder->getDirection() == LEFT)
//    {
//        this->flipDirection(RIGHT);
//        this->body->ApplyLinearImpulse(b2Vec2(-this->data.getSpeed(), 0), b2Vec2(0,0));
//    }
//    else if(holder->getDirection() == RIGHT)
//    {
//        this->flipDirection(LEFT);
//        this->body->ApplyLinearImpulse(b2Vec2(this->data.getSpeed(), 0), b2Vec2(0,0));
//    }
}

NormalProjectile::~NormalProjectile()
{
    this->sprite->release();
}

b2Vec2 NormalProjectile::getStartPosition(GameObject* holder, b2Body* me)
{
    //
    char holder_join_type, this_join_type;
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
    
    CCLOG("%f-%f",anchorA.x,anchorA.y);
    
    b2AABB thisBoudningBox = Util::getBodyBoundingBoxDynamic(body);
    
    CCLOG("%f-%f-%f-%f",thisBoudningBox.lowerBound.x,thisBoudningBox.lowerBound.y,thisBoudningBox.upperBound.x,thisBoudningBox.upperBound.y);

    
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
    CCLOG("%f-%f",anchorA.x,anchorA.y);

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

void NormalProjectile::BeginContact(b2Contact *contact)
{
    CCLOG("Projectile begin");
    contact_count++;
//    remove();
    contact->SetEnabled(false);
}

void NormalProjectile::EndContact(b2Contact *contact)
{
    CCLOG("Projectile end");
    contact_count--;
    if(contact_count <= 0)
    {
        remove();
        contact_count=10;
    }
}

void NormalProjectile::update(float dt)
{
    if(this->sprite != NULL)
    {
        CCPoint bodyPosition = ccp(this->body->GetPosition().x*PTM_RATIO,this->body->GetPosition().y*PTM_RATIO);
        this->sprite->setPosition(bodyPosition);
        this->sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body->GetAngle()));
    }
}


void NormalProjectile::checkCollisionDataInBeginContact(PhysicData* data)
{
    
}

void NormalProjectile::checkCollisionDataInEndContact(PhysicData* data)
{
    
}

void NormalProjectile::remove()
{
    ScheduleManager::getInstance()->scheduleForGameObject(this, 0);
}

 void NormalProjectile::excuteScheduledFunction(CCObject* pSender, void *body)
{
    PhysicBodyManager::getInstance()->addBody((GameObject*)body);
    if(this->sprite)
    {
        ((GameObject*)body)->getSprite()->getParent()->removeChild(((GameObject*)body)->getSprite());
    }
}

void NormalProjectile::setGroup(int group)
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

