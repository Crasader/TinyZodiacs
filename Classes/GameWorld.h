//
//  GameWorld.h
//  Headball
//
//  Created by Nhut on 3/10/14.
//
//

#ifndef __Headball__GameWorld__
#define __Headball__GameWorld__

class GameWorld;

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
#include "EffectManager.h"
#include "Item.h"
#include "ItemFactory.h"
#include "GameManager.h"
#include "GameMatch.h"
#include "Player.h"
#include "ControllerManager.h"

USING_NS_CC;
using namespace std;

class GameWorld: public CCNode, public b2ContactListener
{
private:
    CC_SYNTHESIZE(b2World*, world, World);
    CC_SYNTHESIZE(float, width, Width);
    CC_SYNTHESIZE(float, height, Height);
    CC_SYNTHESIZE_READONLY(float, bottom, Bottom);
    CC_SYNTHESIZE_READONLY(float, left, Left);
    CC_SYNTHESIZE_READONLY(b2Body*, topLine, TopLine);
    CC_SYNTHESIZE_READONLY(b2Body*, leftLine, LeftLine);
    CC_SYNTHESIZE_READONLY(b2Body*, rightLine, RightLine);
    CC_SYNTHESIZE_READONLY(b2Body*, bottomLine, BottomLine);
    CC_SYNTHESIZE(string, mapID, MapID);
    CC_SYNTHESIZE(Map*, map, Map);
    CC_SYNTHESIZE(GameGroup*, group1, Group1);
    CC_SYNTHESIZE(GameGroup*, group2, Group2);
    CC_SYNTHESIZE(Player*, player, player);
    CCAction* cameraFollowAction;
protected:
 
public:
    virtual bool init();
    virtual void update(float dt);
    virtual void draw();
    
    void createWorldBox();
    void onCreate();
    void onCreateMap();
    void onCreateWorld();
    void onCreateUnits();
    void destroy();
    
    void addPlayer(Player* player);

    void addManager();
    GameWorld();
    virtual ~GameWorld();
    

    
    void setCameraFollowGroup(GameGroup* group);
    void setCameraFollowNode(CCNode* nodeFollowed);
    
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    
    void setContactListener(b2ContactListener* listener);
    
    void foo();
    
    CREATE_FUNC(GameWorld);
};

#endif /* defined(__Headball__GameWorld__) */
