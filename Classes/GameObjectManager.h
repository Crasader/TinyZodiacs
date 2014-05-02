//
//  PhysicBodyManager.h
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#ifndef __TinyZodiacs__PhysicBodyManager__
#define __TinyZodiacs__PhysicBodyManager__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameObject.h"

USING_NS_CC;
class GameObjectManager: public CCNode
{
private:
//    static PhysicBodyManager* instance;
protected:
    GameObjectManager();
    ~GameObjectManager();
public:
    CC_SYNTHESIZE(CCArray*, listBody, ListBody);

    CC_SYNTHESIZE(b2World*, world, World)
    
    virtual bool init();
    CREATE_FUNC(GameObjectManager);
    
    void addObject(GameObject* body);
    
    void update(float dt);
    
    static void release();
    
    static GameObjectManager* getInstance();
};
#endif /* defined(__TinyZodiacs__PhysicBodyManager__) */
