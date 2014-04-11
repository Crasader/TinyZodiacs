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
    
    b2AABB aabb = holder->getBodyBoundingBox();
    bodyDef.position = b2Vec2((aabb.lowerBound.x+aabb.upperBound.x)/2+300/32, (aabb.lowerBound.y+aabb.upperBound.y)/2+0/32);
    
    this->body = holder->getBody()->GetWorld()->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, data.getProjectileBodyId());
    
    body->SetGravityScale(this->data.getGravityScale());
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
    
    holder->getSprite()->getParent()->addChild(this->sprite, ABOVE_CHARACTER_LAYER);
    //
    this->body->ApplyLinearImpulse(b2Vec2(this->data.getSpeed(), 0), b2Vec2(0,0));
}

NormalProjectile::~NormalProjectile()
{
    this->sprite->release();
}

void NormalProjectile::BeginContact(b2Contact *contact)
{
    CCLOG("Projectile begin");
    contact_count++;
//    remove();

}

void NormalProjectile::EndContact(b2Contact *contact)
{
    CCLOG("Projectile end");
    contact_count--;
    if(contact_count <= 0)
    {
        remove();
        contact->SetEnabled(false);
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

