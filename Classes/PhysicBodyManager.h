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
class PhysicBodyManager
{
private:
//    static PhysicBodyManager* instance;
protected:
    PhysicBodyManager();
    ~PhysicBodyManager();
public:
    CC_SYNTHESIZE(std::vector<GameObject*>, listBody, ListBody);
    CC_SYNTHESIZE(b2World*, world, World)
    
    void addBody(GameObject* body);
    
    void update(float dt);
    
    static void release();
    
    static PhysicBodyManager* getInstance();
};
#endif /* defined(__TinyZodiacs__PhysicBodyManager__) */
