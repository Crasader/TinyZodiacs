//
//  AnimationEffect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__AnimationEffect__
#define __TinyZodiacs__AnimationEffect__

class AnimationEffect;

#include <iostream>
#include "cocos2d.h"
#include "Effect.h"

USING_NS_CC;

class AnimationEffect: public Effect
{
private:
protected:
    AnimationObject* animationObject;
    CCCallFunc* stopAction;
public:
    CCSprite* sprite;

    AnimationEffect();
    virtual ~AnimationEffect();
    
    virtual bool init();
    virtual void update(float dt);
    
    void run();
    void stop();
    
    void setAnimation(const char* id);
    void setOpacity(GLubyte opacity);
    
    void setStopAction(CCCallFunc* action);
    
    CREATE_FUNC(AnimationEffect);
};

#endif /* defined(__TinyZodiacs__AnimationEffect__) */
