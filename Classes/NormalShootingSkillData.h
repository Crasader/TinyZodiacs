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
#include "ProjectileData.h"

USING_NS_CC;
class NormalShootingSkillData: public SkillData
{
private:
protected:
public:
    NormalShootingSkillData();
    ~NormalShootingSkillData();
    
    CC_SYNTHESIZE(ProjectileData, projectileData, ProjectileData);
    CC_SYNTHESIZE(int, projectileQuantity, ProjectileQuantity);
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, angle, Angle);
    CC_SYNTHESIZE(float, angleVariability, AngleVariability);
    CC_SYNTHESIZE(int, quantity, Quantity);
    CC_SYNTHESIZE(float, delayPerShoot, DelayPerShoot);
    CC_SYNTHESIZE(CCPoint, positionPlusPerUnit, PositionPlusPerUnit);
    
    virtual void clone();
};
#endif /* defined(__TinyZodiacs__NormalShootingSkillData__) */
