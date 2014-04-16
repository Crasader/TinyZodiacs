//
//  NormalShootingSkillData.h
//  TinyZodiacs
//
//  Created by Nhut on 4/4/14.
//
//

#ifndef __TinyZodiacs__NormalShootingSkillData__
#define __TinyZodiacs__NormalShootingSkillData__

#include <iostream>
#include "SkillData.h"

USING_NS_CC;
class NormalShootingSkillData: public SkillData
{
private:
protected:
public:
    NormalShootingSkillData();
    ~NormalShootingSkillData();
    
    CC_SYNTHESIZE(std::string, projectileBodyId, ProjectileBodyId);
    CC_SYNTHESIZE(std::string, animationId, AnimationId);
    CC_SYNTHESIZE(bool, terrainCollide, TerrainCollide);
    CC_SYNTHESIZE(float, gravityScale, GravityScale);
    CC_SYNTHESIZE(float, speed, Speed);
};
#endif /* defined(__TinyZodiacs__NormalShootingSkillData__) */
