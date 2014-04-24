//
//  MoveableMapObject.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/31/14.
//
//

#ifndef __TinyZodiacs__MoveableMapObject__
#define __TinyZodiacs__MoveableMapObject__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MapObject.h"

class MoveableMapObject: public MapObject
{
private:
protected:
public:
    MoveableMapObject();
    ~MoveableMapObject();
    
    virtual void update(float dt);
    b2Body* controller;
    
    
    CREATE_FUNC(MoveableMapObject);
};

#endif /* defined(__TinyZodiacs__MoveableMapObject__) */
