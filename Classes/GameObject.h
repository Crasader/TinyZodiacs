//
//  GameObject.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__GameObject__
#define __SampleCocosProject__GameObject__

#include <iostream>
#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "PhysicConstants.h"
#include "PhysicData.h"

enum Direction {LEFT, RIGHT};
class GameObject: public cocos2d::CCObject
{
private:
   
protected:
    Direction direction;
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);

public:
    GameObject();
    ~GameObject();
    float32 isPassingThroughBody;
    CC_SYNTHESIZE(cocos2d::CCSprite*, sprite, Sprite);
    CC_SYNTHESIZE(b2Body*, body, Body);
    CC_SYNTHESIZE(cocos2d::CCPoint, spriteAnchorPoint, SpriteAnchorPoint);
    
    Direction getDirection();
    b2AABB getBodyBoundingBox();
    
    void setAnchorPointForAnimation1(const cocos2d::CCPoint &anchorPoint);
    void flipDirection(Direction direction);
    
    virtual void setSkin(b2Body* body,cocos2d::CCSprite* sprite);
    virtual bool init();
    virtual void update(float dt);
    virtual void setPositionInPixel(const cocos2d::CCPoint& pos);
    virtual cocos2d::CCPoint getPositionInPixel();
    virtual void updateSpritePositionWithBodyPosition();
    
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
  
    virtual void excuteScheduledFunction(CCObject* pSender, void *body);
    virtual void setGroup(uint16 group);
    virtual uint16 getGroup();
};

#endif /* defined(__SampleCocosProject__GameObject__) */
