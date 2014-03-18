//
//  GameObject.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#include "GameObject.h"
#include "Box2D/Box2d.h"

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
    
}

void GameObject::EndContact(b2Contact *conact)
{
    
}

void GameObject::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    
}

void GameObject::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    
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
}