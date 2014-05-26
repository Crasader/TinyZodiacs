//
//  Effect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#ifndef __TinyZodiacs__Effect__
#define __TinyZodiacs__Effect__

class Effect;

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"

USING_NS_CC;

class Effect: public CCNode
{
private:
protected:
public:
    Effect();
    virtual ~Effect();
    
    virtual bool init();
    virtual void update(float dt) = 0;
    
    virtual void run() = 0;
    virtual void stop() = 0;
};

#endif /* defined(__TinyZodiacs__Effect__) */
