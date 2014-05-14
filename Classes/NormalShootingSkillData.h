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
#include "AnimationObject.h"

USING_NS_CC;
class NormalShootingSkillData: public SkillData
{
private:
protected:
public:
    NormalShootingSkillData();
    ~NormalShootingSkillData();
    
    CC_SYNTHESIZE(std::string, projectileBodyId, ProjectileBodyId);
    CC_SYNTHESIZE(AnimationObject*, animation, Animation);
    CC_SYNTHESIZE(float, rotateAngle, RotateAngle);
    CC_SYNTHESIZE(bool, terrainCollide, TerrainCollide);
    CC_SYNTHESIZE(bool, piercing, Piercing);
    CC_SYNTHESIZE(float, gravityScale, GravityScale);
    CC_SYNTHESIZE(float, speedX, SpeedX);
    CC_SYNTHESIZE(float, speedY, SpeedY);

    CC_SYNTHESIZE(int, animationLayerIndex, AnimationLayerIndex);
    
    virtual void clone();
};
#endif /* defined(__TinyZodiacs__NormalShootingSkillData__) */
