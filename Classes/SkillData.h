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
#include "Constants.h"

USING_NS_CC;

class SkillData
{
private:
protected:
public:
    SkillData();
    ~SkillData();
    
    CC_SYNTHESIZE(float, coolDown, CoolDown);
    CC_SYNTHESIZE(float, delay, Delay);
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CC_SYNTHESIZE(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE(JointDef, jointDefB, JointDefB);
    CC_SYNTHESIZE(SkillTarget, target, Target)
    CC_SYNTHESIZE(CCArray*, listEnemyEffect, ListEnemyEffect);
    CC_SYNTHESIZE(CCArray*, listAlliesEffect, ListAlliesEffect);

};
#endif /* defined(__TinyZodiacs__SkillData__) */
