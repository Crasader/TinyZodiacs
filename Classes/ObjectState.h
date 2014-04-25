//
//  ObjectState.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__ObjectState__
#define __Headball__ObjectState__

#include <iostream>
#include "Character.h"

class ObjectState: public CCObject
{
private:
protected:
public:
    ObjectState();
    ~ObjectState();

    virtual void update(float dt) = 0;
    
    virtual bool onEnterState();
    virtual bool onExitState();
};
#endif /* defined(__Headball__ObjectState__) */
