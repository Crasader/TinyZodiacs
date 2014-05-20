//
//  GameObject.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__GameObject__
#define __SampleCocosProject__GameObject__
class GameObject;
#include <iostream>
#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "PhysicConstants.h"
#include "PhysicData.h"
#include "GameObjectView.h"
#include "Observable.h"
#include "Observer.h"

USING_NS_CC;

enum Direction {LEFT, RIGHT};

class GameObject: public cocos2d::CCObject, public Observable
{
private:
    
protected:
    bool isDestroyed;
    cocos2d::CCArray* listEffect;
    Direction direction;
    CC_SYNTHESIZE(GameObjectID, gameObjectID, GameObjectID);
    CC_SYNTHESIZE(CCSprite*, sprite, Sprite);
    CC_SYNTHESIZE(b2Body*, body, Body);
    CC_SYNTHESIZE(CCPoint, spriteAnchorPoint, SpriteAnchorPoint);
    CC_SYNTHESIZE_READONLY(Group, group, Group);
    
    GameObjectView* gameObjectView;
    
    virtual void updateAllEffect(float dt);
    
    virtual uint16 getCorrectGroup(Group group);
    virtual void setPhysicGroup(uint16 group);
public:
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    GameObject();
    ~GameObject();
    float32 isPassingThroughBody;
    
    
    Direction getDirection();
    b2AABB getBodyBoundingBox();
    
    void setAnchorPointForAnimation1(const CCPoint &anchorPoint);
    void flipDirection(Direction direction);
    
    virtual void setSkin(b2Body* body, CCSprite* sprite);
    virtual bool init();
    virtual void update(float dt);
    virtual void updateGameObjectView(float dt);
    virtual void setPositionInPixel(const CCPoint& pos);
    virtual cocos2d::CCPoint getPositionInPixel();
    virtual b2Vec2 getPositionInPhysicWorld();
    virtual void setGameObjectView(GameObjectView* gameObjectView);
    virtual void onCreate();
    
    virtual void attachSpriteTo(CCNode* node);
    
    virtual void updateSpritePositionWithBodyPosition();
    
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    virtual void excuteScheduledFunction(CCObject* pSender, void *body);
    virtual void setGroup(Group group);
    virtual uint16 getPhysicGroup();
    
    virtual void applyEffect(CCObject* effect);
    virtual void removeEffect(CCObject* object);
    virtual void notifyByEffect(CCObject* effect);
    virtual void destroy();
    
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notifyToDestroy();

};

#endif /* defined(__SampleCocosProject__GameObject__) */
