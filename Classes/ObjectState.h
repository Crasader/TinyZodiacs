//
//  ObjectState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__ObjectState__
#define __Headball__ObjectState__

class ObjectState;

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ObjectState: public CCObject
{
private:
protected:
public:
    ObjectState();
    ~ObjectState();
    
    virtual bool init();

    virtual void update(float dt) = 0;
    
    virtual bool onEnterState() = 0;
    virtual bool onExitState() = 0;
};
#endif /* defined(__Headball__ObjectState__) */
