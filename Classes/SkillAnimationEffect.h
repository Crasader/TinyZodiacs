//
//  SkillAnimationEffect.h
//  TinyZodiacs
//
//  Created by NhutVM on 5/21/14.
//
//

#ifndef __TinyZodiacs__SkillAnimationEffect__
#define __TinyZodiacs__SkillAnimationEffect__

class SkillAnimationEffect;

#include <iostream>
#include "cocos2d.h"
#include "AnimationEffect.h"

USING_NS_CC;

class SkillAnimationEffect: public AnimationEffect
{
private:
protected:
    CCAction* action;
    
    CC_SYNTHESIZE(float, minRotateAngle, MinRotateAngle);
    CC_SYNTHESIZE(float, maxRotateAngle, MaxRotateAngle);
    CC_SYNTHESIZE(float, minScale, MinScale);
    CC_SYNTHESIZE(float, maxScale, MaxScale);
    CC_SYNTHESIZE(int, repeatTimes, RepeatTimes);
    
    CC_SYNTHESIZE(bool, isFiniteAction, IsFiniteAction);
public:
    SkillAnimationEffect();
    virtual ~SkillAnimationEffect();
    
    void setPosition(CCPoint newPosition);
    
    virtual bool init();
    
    virtual void update(float dt);
    
    virtual void run();
    virtual void stop();
    
//    void setAnimation(const char* id);
    void setAnimation(const char* id, float minRotate, float maxRotate, float minScale, float maxScale, int repeatTimes, CCPoint position);
    
    float getAnimationDuration();
    
    CREATE_FUNC(SkillAnimationEffect);
    
};

#endif /* defined(__TinyZodiacs__SkillAnimationEffect__) */
