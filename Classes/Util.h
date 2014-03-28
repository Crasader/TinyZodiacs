//
//  Util.h
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#ifndef __TinyZodiacs__Util__
#define __TinyZodiacs__Util__

#include <iostream>
#include "Box2D/Box2D.h"
#include "PhysicConstants.h"

class Util
{
private:
protected:
public:
    static b2AABB getBodyBoundingBox(b2Body* body);
    static b2Vec2 getb2VecAnchor(b2Body* body, JointDef jointDef);
};

#endif /* defined(__TinyZodiacs__Util__) */
