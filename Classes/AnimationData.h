//
//  AnimationData.h
//  TinyZodiacs
//
//  Created by NhutVM on 5/31/14.
//
//

#ifndef __TinyZodiacs__AnimationData__
#define __TinyZodiacs__AnimationData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class AnimationData: public CCObject
{
    CC_SYNTHESIZE(std::string, animationId, AnimationId);
    CC_SYNTHESIZE(int, animationLayerIndex, AnimationLayerIndex);
    CC_SYNTHESIZE(float, minRotateAngle, MinRotateAngle);
    CC_SYNTHESIZE(float, maxRotateAngle, MaxRotateAngle);
    CC_SYNTHESIZE(float, minScale, MinScale);
    CC_SYNTHESIZE(float, maxScale, MaxScale);
    CC_SYNTHESIZE(int, repeatTimes, RepeatTimes);
};

#endif /* defined(__TinyZodiacs__AnimationData__) */
