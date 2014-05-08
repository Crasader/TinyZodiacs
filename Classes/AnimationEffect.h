//
//  AnimationEffect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__AnimationEffect__
#define __TinyZodiacs__AnimationEffect__

#include <iostream>
#include "cocos2d.h"
#include "GameEffect.h"
#include "DataCollector.h"

USING_NS_CC;

class AnimationEffect: public GameEffect
{
private:
    CCSprite* sprite;
    AnimationObject* animationObject;
protected:
public:
    AnimationEffect();
    virtual ~AnimationEffect();
    
    virtual bool init();
    virtual void update(float dt);
    
    void run();
    void stop();
    
    void setAnimation(const char* id);
    
    CREATE_FUNC(AnimationEffect);
};

#endif /* defined(__TinyZodiacs__AnimationEffect__) */
