//
//  ProjectileData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#ifndef __TinyZodiacs__ProjectileData__
#define __TinyZodiacs__ProjectileData__

#include <iostream>
#include "cocos2d.h"
#include "ProjectileStateAnimationData.h"
#include "ProjectileSoundData.h"
#include "Constants.h"

USING_NS_CC;
class ProjectileData
{
private:
protected:
public:
    CC_SYNTHESIZE(ApplyType, applyType, ApplyType);
    CC_SYNTHESIZE(std::string, projectileBodyId, ProjectileBodyId);
    CC_SYNTHESIZE(ProjectileStateAnimationData, stateAnimation, StateAnimation);
    CC_SYNTHESIZE(ProjectileSoundData, soundData, SoundData);
    CC_SYNTHESIZE(bool, terrainCollide, TerrainCollide);
    CC_SYNTHESIZE(int, piercing, Piercing);
    CC_SYNTHESIZE(float, gravityScale, GravityScale);
};
#endif /* defined(__TinyZodiacs__ProjectileData__) */
