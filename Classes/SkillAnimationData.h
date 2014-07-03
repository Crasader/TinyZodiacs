//
//  SkillAnimationData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/28/14.
//
//

#ifndef __TinyZodiacs__SkillAnimationData__
#define __TinyZodiacs__SkillAnimationData__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"

USING_NS_CC;
class SkillAnimationData
{
private:
protected:
public:
    CC_SYNTHESIZE(AnimationObject*, preExcuteAnimation, PreExcuteAnimation);
    CC_SYNTHESIZE(AnimationObject*, excuteAnimation, ExcuteAnimation);
    CC_SYNTHESIZE(AnimationObject*, preStopAnimation, PreStopAnimation);
    CC_SYNTHESIZE(AnimationObject*, stopAnimation, StopAnimation);
    
    bool haveAnyData();
};
#endif /* defined(__TinyZodiacs__SkillAnimationData__) */
