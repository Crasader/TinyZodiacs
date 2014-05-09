//
//  GameEffect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#ifndef __TinyZodiacs__GameEffect__
#define __TinyZodiacs__GameEffect__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"

USING_NS_CC;

class GameEffect: public CCNode
{
private:
protected:
public:
    GameEffect();
    virtual ~GameEffect();
    
    virtual bool init();
    virtual void update(float dt) = 0;
    
    virtual void run() = 0;
    virtual void stop() = 0;
};

#endif /* defined(__TinyZodiacs__GameEffect__) */
