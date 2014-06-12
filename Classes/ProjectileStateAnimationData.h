//
//  ProjectileStateAnimationData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#ifndef __TinyZodiacs__ProjectileStateAnimationData__
#define __TinyZodiacs__ProjectileStateAnimationData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class ProjectileStateAnimationData
{
private:
protected:
public:
    CC_SYNTHESIZE(int, animationLayerIndex, AnimationLayerIndex);
    CC_SYNTHESIZE(std::string, createdStateAnimationID, CreatedStateAnimationID);
    CC_SYNTHESIZE(std::string, shootingStateAnimationID, ShootingStateAnimationID);
    CC_SYNTHESIZE(std::string, hitStateAnimationID, HitStateAnimationID);
    CC_SYNTHESIZE(std::string, dieStateAnimationID, DieStateAnimationID);
};
#endif /* defined(__TinyZodiacs__ProjectileStateAnimationData__) */
