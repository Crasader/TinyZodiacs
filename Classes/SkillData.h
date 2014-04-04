//
//  SkillData.h
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#ifndef __TinyZodiacs__SkillData__
#define __TinyZodiacs__SkillData__

#include <iostream>
#include "cocos2d.h"
#include "PhysicConstants.h"

USING_NS_CC;

class SkillData
{
private:
protected:
public:
    CC_SYNTHESIZE(int, damage, Damage);
    CC_SYNTHESIZE(float, coolDown, CoolDown);
    CC_SYNTHESIZE(float, delay, Delay);
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CC_SYNTHESIZE(float, critical, Critical);
    CC_SYNTHESIZE(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE(JointDef, jointDefB, JointDefB);
};
#endif /* defined(__TinyZodiacs__SkillData__) */
