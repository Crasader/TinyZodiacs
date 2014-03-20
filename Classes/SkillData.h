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
#include "Box2D/Box2D.h"

USING_NS_CC;
class SkillData
{
private:
protected:
public:
    CC_SYNTHESIZE(int, damage, Damage);
    CC_SYNTHESIZE(int, speed, Speed);
    
    CC_SYNTHESIZE(CCPoint, location, Location);
    CC_SYNTHESIZE(b2Body*, skillSensor, SkillSensor);
};
#endif /* defined(__TinyZodiacs__SkillData__) */
