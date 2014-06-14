//
//  GameObjectCalculateData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/13/14.
//
//

#ifndef __TinyZodiacs__GameObjectCalculateData__
#define __TinyZodiacs__GameObjectCalculateData__

#include <iostream>

#include <iostream>
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "Constants.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

class GameObjectCalculateData
{
private:
protected:
public:
    CC_SYNTHESIZE(b2AABB, bodyBoundinBox, bodyBoundingBox);
    CC_SYNTHESIZE(b2AABB, bodyBoundinBoxDynamic, bodyBoundingBoxDynamic);
    CC_SYNTHESIZE(Direction, direction, Direction);
    CC_SYNTHESIZE(b2Vec2, speed, Speed);
    CC_SYNTHESIZE(Group, group, Group);
};


#endif /* defined(__TinyZodiacs__GameObjectCalculateData__) */
