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
USING_NS_CC;
class GameWorld: public CCNode
{
private:
protected:
    bool init();
    void createWorldBox();
public:
    CC_SYNTHESIZE(b2World*, world, World);
    CC_SYNTHESIZE_READONLY(float, width, Width);
    CC_SYNTHESIZE_READONLY(float, height, Height);
    CC_SYNTHESIZE_READONLY(float, bottom, Bottom);
    CC_SYNTHESIZE_READONLY(float, left, Left);
    CC_SYNTHESIZE_READONLY(b2Body*, topLine, TopLine);
    CC_SYNTHESIZE_READONLY(b2Body*, leftLine, LeftLine);
    CC_SYNTHESIZE_READONLY(b2Body*, rightLine, RightLine);
    CC_SYNTHESIZE_READONLY(b2Body*, bottomLine, BottomLine);


    GameWorld(float bottom, float left, float width, float height);
    void setContactListener(b2ContactListener* listener);
};

#endif /* defined(__Headball__GameWorld__) */
