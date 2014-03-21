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

USING_NS_CC;
class PhysicBodyManager
{
private:
//    static PhysicBodyManager* instance;
protected:
    PhysicBodyManager();
    ~PhysicBodyManager();
public:
    CC_SYNTHESIZE(std::vector<b2Body*>, listBody, ListBody);
    CC_SYNTHESIZE(b2World*, world, World)
    
    void addBody(b2Body* body);
    
    void update(float dt);
    
    static PhysicBodyManager* getInstance();
};
#endif /* defined(__TinyZodiacs__PhysicBodyManager__) */
