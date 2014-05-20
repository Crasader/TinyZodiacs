//
//  GameObject.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#include "GameObject.h"
#include "Box2D/Box2d.h"
#include "Util.h"
#include "GameObjectManager.h"
#include "Effect.h"

USING_NS_CC;

GameObject::GameObject()
{
    this->gameObjectID = NONE;
    this->isPassingThroughBody = 0;
    this->body = NULL;
    this->sprite = NULL;
    this->gameObjectView = NULL;
    direction = LEFT;
    
    this->listEffect = CCArray::create();
    this->listEffect->retain();
    
    init();
}

GameObject::~GameObject()
{
    if(this->sprite != NULL)
    {
        this->sprite->removeFromParent();
    }
    
    if(this->body != NULL)
    {
        for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
        {
            f->SetUserData(NULL);
        }
        this->body->GetWorld()->DestroyBody(this->body);
    }
    
    CCObject* object;
    CCARRAY_FOREACH(this->listEffect, object)
    {
        ((Effect*)object)->stopAllSchedule();
    }
    this->listEffect->removeAllObjects();
    
    //game object view
    if(this->gameObjectView != NULL)
        
    {
        this->gameObjectView->removeFromParent();
        this->gameObjectView->release();
    }
    
    
    //    CC_SAFE_RELEASE(this->listEffect);
}

bool GameObject::init()
{
    
    return true;
}

void GameObject::onCreate()
{
    //
}

void GameObject::excuteScheduledFunction(CCObject* pSender, void *body)
{
    
}


void GameObject::update(float dt)
{
//    if(this->sprite != NULL)
//    {
//        this->sprite->setScale(0);
//    }
    
    updateSpritePositionWithBodyPosition();
    updateAllEffect(dt);
    updateGameObjectView(dt);
}

void GameObject::updateGameObjectView(float dt)
{
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->update(dt);
    }
}

void GameObject::setGameObjectView(GameObjectView* gameObjectView)
{
    this->gameObjectView = gameObjectView;
}

void GameObject::setPositionInPixel(const cocos2d::CCPoint &pos)
{
    b2Vec2 bodyPosition = b2Vec2(pos.x/PTM_RATIO, pos.y/PTM_RATIO) ;
    this->body->SetTransform(bodyPosition, this->body->GetAngle());
    
    updateSpritePositionWithBodyPosition();
}

void GameObject::attachSpriteTo(CCNode* node)
{
    node->addChild(this->gameObjectView,GAME_OBJECT_VIEW);
}

CCPoint GameObject::getPositionInPixel()
{
    CCPoint position = ccp(this->body->GetPosition().x*PTM_RATIO,this->body->GetPosition().y*PTM_RATIO);
    
    
    return position;
}

b2Vec2 GameObject::getPositionInPhysicWorld()
{
    return this->getBody()->GetPosition();
}

void GameObject::setSkin(b2Body *body, cocos2d::CCSprite *sprite)
{
    setBody(body);
    setSprite(sprite);
    
    updateSpritePositionWithBodyPosition();
}

void GameObject::updateSpritePositionWithBodyPosition()
{
    if(this->body != NULL && this->sprite != NULL)
    {
        CCPoint bodyPosition = this->getPositionInPixel();
        
        this->sprite->setPosition(bodyPosition);
        
        this->sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body->GetAngle()));
    }
    
}

void GameObject::updateAllEffect(float dt)
{
    CCObject* effect;
    CCARRAY_FOREACH(this->listEffect, effect)
    {
        ((Effect*)effect)->update(dt);
    }
}

void GameObject::setAnchorPointForAnimation1(const cocos2d::CCPoint &anchorPoint)
{
    if(this->direction == LEFT)
    {
        this->sprite->setAnchorPoint(anchorPoint);
    }
    else
    {
        this->sprite->setAnchorPoint(ccp(1-anchorPoint.x,anchorPoint.y));
        
    }
}

void GameObject::flipDirection(Direction direction)
{
    if(this->direction != direction)
    {
        this->direction = direction;
        if(this->sprite!=NULL)
        {
            if(direction == LEFT)
            {
                this->sprite->setFlipX(false);
            }
            else
            {
                this->sprite->setFlipX(true);
                
            }
            this->sprite->setAnchorPoint(ccp(1 - this->getSprite()->getAnchorPoint().x,this->getSprite()->getAnchorPoint().y));
        }
    }
}

void GameObject::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();

        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
    
}
void GameObject::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInEndContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInEndContact(holderData, collisionData,contact);
    }
}

void GameObject::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    //   CCLOG("presolve");
    
    //    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    //    {
    //        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
    //        checkCollisionDataInBeginContact(data, contact, true);
    //    }
    //
    //    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    //    {
    //        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
    //        checkCollisionDataInBeginContact(data, contact, false);
    //    }
    
    
}
void GameObject::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    //  CCLOG("postsolve");
    //    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    //    {
    //        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
    //        checkCollisionDataInBeginContact(data, contact, true);
    //    }
    //
    //    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    //    {
    //        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
    //        checkCollisionDataInBeginContact(data, contact, false);
    //    }
    //
}

void GameObject::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
}
void GameObject::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
}
Direction GameObject::getDirection()
{
    return this->direction;
}


b2AABB GameObject::getBodyBoundingBox()
{
    if(this->body != NULL)
    {
        //Calculate b
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = this->body->GetFixtureList();
        while (fixture != NULL)
        {
            aabb.Combine(aabb, fixture->GetAABB(0));
            fixture = fixture->GetNext();
        }
        return aabb;
    }
    
    
    return b2AABB();
    //    return Util::getBodyBoundingBox(this->getBody());
}

void GameObject::setPhysicGroup(uint16 group)
{
    if(this->body != NULL)
    {
        for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
        {
            if(f != NULL)
            {
                Util::setFixtureGroup(f, group);
            }
        }
        
    }
}


void  GameObject::setGroup(Group group)
{
    this->group = group;
    this->setPhysicGroup(getCorrectGroup(group));
}

uint16  GameObject::getCorrectGroup(Group group)
{
    switch (group)
    {
        case A:
            return GROUP_A;
            break;
        case B:
            return GROUP_B;
        case NEUTRAL:
            return GROUP_NEUTRUAL;
        case TERRAIN:
            return GROUP_TERRAIN;
        case ITEM:
            return GROUP_ITEM;
    }
}

uint16 GameObject::getPhysicGroup()
{
    return this->body->GetFixtureList()->GetFilterData().categoryBits;
}

void GameObject::applyEffect(CCObject* effect)
{
    this->listEffect->addObject(effect);
}

void GameObject::removeEffect(CCObject* object)
{
    this->listEffect->removeObject(object);
}

void GameObject::notifyByEffect(CCObject* effect)
{
    
}

void GameObject::destroy()
{
    
}

void GameObject::attach(Observer* observer)
{
    this->listObserver.push_back(observer);
}

void GameObject::detach(Observer* observer)
{
    for( std::vector<Observer*>::iterator iter = this->listObserver.begin(); iter != this->listObserver.end(); ++iter )
    {
        if( *iter == observer )
        {
            this->listObserver.erase( iter );
            break;
        }
    }
}

void GameObject::notifyToDestroy()
{
    for(int i = 0 ; i < this->listObserver.size() ; i++)
    {
        this->listObserver[i]->notifyToDestroy(this);
    }
}