//
//  Wall.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#ifndef __TinyZodiacs__Wall__
#define __TinyZodiacs__Wall__
class Wall;

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"
USING_NS_CC;
using namespace std;

class Wall: public GameObject
{
private:
    CC_SYNTHESIZE(bool, deadWall, DeadWall);
protected:
public:
    Wall();
    ~Wall();
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(Wall);
    
};

#endif /* defined(__TinyZodiacs__Wall__) */
