//
//  GameWorld.h
//  Headball
//
//  Created by Nhut on 3/10/14.
//
//

#ifndef __Headball__GameWorld__
#define __Headball__GameWorld__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2d.h"
#include "PhysicConstants.h"
#include "Character.h"
#include "Map.h"
#include "NormalAttack.h"
#include "GameObjectManager.h"
#include "HealthBar.h"
#include "ScheduleManager.h"
#include "Monster.h"
#include "Tower.h"
#include "GameGroup.h"

USING_NS_CC;
class GameWorld: public CCNode, public b2ContactListener
{
private:
    GameObjectManager* manager;
    CCArray* listInfoView;
    int count;
    CCAction* cameraFollowAction;
protected:
    bool init();
    void createWorldBox();
public:
    CC_SYNTHESIZE(b2World*, world, World);
    CC_SYNTHESIZE(float, width, Width);
    CC_SYNTHESIZE(float, height, Height);
    CC_SYNTHESIZE_READONLY(float, bottom, Bottom);
    CC_SYNTHESIZE_READONLY(float, left, Left);
    CC_SYNTHESIZE_READONLY(b2Body*, topLine, TopLine);
    CC_SYNTHESIZE_READONLY(b2Body*, leftLine, LeftLine);
    CC_SYNTHESIZE_READONLY(b2Body*, rightLine, RightLine);
    CC_SYNTHESIZE_READONLY(b2Body*, bottomLine, BottomLine);
  
    CC_SYNTHESIZE(Map*, map, map);
    CC_SYNTHESIZE(GameGroup*, group1, Group1);
    CC_SYNTHESIZE(GameGroup*, group2, Group2);

    Character* getCharacter();
    
    void foo();
    void foo1();
    

    
    GameWorld();
    virtual ~GameWorld();
    
    
    virtual void update(float dt);
    virtual void draw();
    
    void setCameraFollowGroup(GameGroup* group);

    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    void setContactListener(b2ContactListener* listener);
    
    void addManager();
    
    CREATE_FUNC(GameWorld);
};

#endif /* defined(__Headball__GameWorld__) */
