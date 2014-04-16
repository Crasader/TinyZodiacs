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

USING_NS_CC;

GameObject::GameObject()
{
    direction = LEFT;
    init();
}

GameObject::~GameObject()
{
    
}

bool GameObject::init()
{
    
    return true;
}

void GameObject::excuteScheduledFunction(CCObject* pSender, void *body)
{
    
}


void GameObject::update(float dt)
{
    updateSpritePositionWithBodyPosition();
}

void GameObject::setPositionInPixel(const cocos2d::CCPoint &pos)
{
    b2Vec2 bodyPosition = b2Vec2(pos.x/PTM_RATIO, pos.y/PTM_RATIO) ;
    this->body->SetTransform(bodyPosition, this->body->GetAngle());
    
    updateSpritePositionWithBodyPosition();
}

CCPoint GameObject::getPositionInPixel()
{
    CCPoint position = ccp(this->body->GetPosition().x*PTM_RATIO,this->body->GetPosition().y*PTM_RATIO);
    return position;
}

void GameObject::setSkin(b2Body *body, cocos2d::CCSprite *sprite)
{
    setBody(body);
    setSprite(sprite);
    
    updateSpritePositionWithBodyPosition();
}

void GameObject::updateSpritePositionWithBodyPosition()
{
    CCPoint bodyPosition = this->getPositionInPixel();
    
    this->sprite->setPosition(bodyPosition);
    
    this->sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body->GetAngle()));
    
}

void GameObject::setAnchorPointForAnimation(const cocos2d::CCPoint &anchorPoint)
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
        if(direction == LEFT)
        {
            this->sprite->setFlipX(false);
        }
        else
        {
            this->sprite->setFlipX(true);
            
        }
        this->sprite->setAnchorPoint(ccp(1 - this->sprite->getAnchorPoint().x,this->sprite->getAnchorPoint().y));
    }
}

void GameObject::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, false);
    }
}
void GameObject::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, false);
    }
}
void GameObject::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    
}
void GameObject::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
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

void GameObject::setGroup(uint16 group)
{
    if(this->body != NULL)
    {
        //        for (b2Fixture* f = this->body->GetFixtureList()
        //             ; f; f = f->GetNext())
        //        {
        //            if(f != NULL)
        //            {
        //                Util::setFixtureGroup(f, group);
        //            }
        //        }
        
        for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
        {
            if(f != NULL)
            {
                Util::setFixtureGroup(f, group);
                
//                if(f->GetNext() != NULL)
//                {
//                    b2Filter filter = f->GetFilterData();
//                    filter.maskBits = filter.maskBits ^ GROUP_SKILL_DEFAULT;
//                    f->SetFilterData(filter);
//                }
            }
        }
        
    }
}

uint16 GameObject::getGroup()
{
    return this->body->GetFixtureList()->GetFilterData().categoryBits;
}