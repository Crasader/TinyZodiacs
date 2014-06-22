//
//  SkillType1Parser.cpp
//  TinyZodiacs
//
//  Created by Nhut on 4/4/14.
//
//

#include "SkillType1Parser.h"

float SkillType1Parser::readProjectileSpeed(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

ProjectileData SkillType1Parser::readProjectileData(const XMLElement* root)
{
    return XMLProjectileDataParser::parseData(XMLHelper::readString(root,""));
}

int SkillType1Parser::readQuantity(const XMLElement* root)
{
    return XMLHelper::readInt(root, 1);
}

float SkillType1Parser::readDelayPerShoot(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

float SkillType1Parser::readAngleVaribility(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

CCPoint SkillType1Parser::readPositionPlus(const XMLElement* root)
{
    return CCPoint(XMLHelper::readAttributeFloat(root, ATTRIBUTE_PLUS_X, 0), XMLHelper::readAttributeFloat(root, ATTRIBUTE_PLUS_Y, 0));
}


NormalShootingSkillData SkillType1Parser::parse(const XMLElement* root, b2World* world)
{
    NormalShootingSkillData data;
    data.setAngle(0);
    data.setCoolDown(readCoolDown(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setLifeTime(readLifeTime(root->FirstChildElement(TAG_LIFE_TIME)));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
    data.setSpeed(readProjectileSpeed(root->FirstChildElement(TAG_SPEED)));
    data.setTarget(readTarget(root->FirstChildElement(TAG_TARGET)));
    data.setProjectileData(readProjectileData(root->FirstChildElement(TAG_PROJECTILE)));
    data.setQuantity(readQuantity(root->FirstChildElement(TAG_QUANTITY)));
    data.setDelayPerShoot(readDelayPerShoot(root->FirstChildElement(TAG_DELAY_PER_SHOOT)));
    data.setAngleVariability(readAngleVaribility(root->FirstChildElement(TAG_ANGLE_VARIBILITY)));
    data.setTimeTick(readTimeTick(root->FirstChildElement(TAG_TIME_TICK)));
    data.setPositionPlusPerUnit(readPositionPlus(root->FirstChildElement(TAG_POSITION_PLUS_PER_UNIT)));
    
    if(root->FirstChildElement(TAG_LIST_EFFECT) != NULL)
    {
        data.setListEnemyEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ENEMY)));

        data.setListAlliesEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ALLIES)));

        data.setlistSelfEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_SELF)));
    }
    // check if skill override peircing value
    const XMLElement* temp = root->FirstChildElement(TAG_PIERCING);
    if(temp)
    {
        ProjectileData newData = data.getProjectileData();
        newData.setPiercing(XMLHelper::readInt(temp, data.getProjectileData().getPiercing()));
        data.setProjectileData(newData);
    }
    
    if(data.getAngleVariability() != 0)
    {
        data.setAngleType(FREE_STYLE);
    }
    else
    {
        data.setAngleType(HOLDER_DIRECTION);
    }
    return data;
}