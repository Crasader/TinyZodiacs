//
//  NormalMeleeSkillData.h
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#ifndef __TinyZodiacs__NormalMeleeSkillData__
#define __TinyZodiacs__NormalMeleeSkillData__

#include <iostream>
#include "SkillData.h"
#include "Box2D/Box2D.h"

class NormalMeleeSkillData: public SkillData
{
private:
protected:
public:
    CC_SYNTHESIZE(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE(JointDef, jointDefB, JointDefB);
    CC_SYNTHESIZE(b2Body*, skillSensor, skillSensor);
};

#endif /* defined(__TinyZodiacs__NormalMeleeSkillData__) */
