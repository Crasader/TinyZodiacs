//
//  SkillType1Parser.h
//  TinyZodiacs
//
//  Created by Nhut on 4/4/14.
//
//

#ifndef __TinyZodiacs__SkillType1Parser__
#define __TinyZodiacs__SkillType1Parser__

#include <iostream>
#include "SkillType0Parser.h"
#include "NormalShootingSkillData.h"
#include "XMLProjectileDataParser.h"

#define TAG_PROJECTILE "projectile"
#define TAG_SPEED "speed"
#define TAG_QUANTITY "quantity"
#define TAG_DELAY_PER_SHOOT "delay_per_shoot"
#define TAG_ANGLE_VARIBILITY "angle_variability"
#define TAG_POSITION_PLUS_PER_UNIT "position_plus_per_unit"

#define ATTRIBUTE_PLUS_X "plus_x"
#define ATTRIBUTE_PLUS_Y "plus_y"

class SkillType1Parser: public SkillType0Parser
{
private:
protected:
    static float readProjectileSpeed(const XMLElement* root);
    static int readQuantity(const XMLElement* root);
    static float readDelayPerShoot(const XMLElement* root);
    static float readAngleVaribility(const XMLElement* root);
    static CCPoint readPositionPlus(const XMLElement* root);

    static ProjectileData readProjectileData(const XMLElement* root);
public:
    static NormalShootingSkillData parse(const XMLElement* root, b2World* world);
};
#endif /* defined(__TinyZodiacs__SkillType1Parser__) */
