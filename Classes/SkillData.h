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
};
#endif /* defined(__TinyZodiacs__SkillData__) */
