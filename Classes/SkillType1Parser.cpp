//
//  SkillType1Parser.cpp
//  TinyZodiacs
//
//  Created by Nhut on 4/4/14.
//
//

#include "SkillType1Parser.h"

string SkillType1Parser::readProjectileBodyId(const XMLElement* root)
{
    if(root != NULL)
    {
        string value = root->GetText();
        return value;
    }
    return "";
}

//CCAnimation* SkillType1Parser::readProjectileAnimationId(const XMLElement* root)
//{
//    if(root != NULL)
//    {
//        string value = root->GetText();
//        return value;
//    }
//    return "";
//}

float SkillType1Parser::readProjectileSpeed(const XMLElement* root)
{
    if(root != NULL)
    {
        string textValue = root->GetText();
        float value = atof(textValue.c_str());
        return value;
    }
    return 0;
}

float SkillType1Parser::readProjectileGravityScale(const XMLElement* root)
{
    if(root != NULL)
    {
        string textValue = root->GetText();
        float value = atof(textValue.c_str());
        return value;
    }
    return 0;
}

bool SkillType1Parser::readTerrainCollide(const XMLElement* root)
{
    if(root != NULL)
    {
        string textValue = root->GetText();
        bool value = atoi(textValue.c_str());
        return value;
    }
    return false;
}

NormalShootingSkillData SkillType1Parser::parse(const XMLElement* root, b2World* world)
{
    NormalShootingSkillData data;
    data.setDamage(readDamage(root->FirstChildElement(TAG_DAMAGE)));
    data.setCoolDown(readDamage(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setLifeTime(readDelay(root->FirstChildElement(TAG_LIFE_TIME)));
    data.setProjectileBodyId(readProjectileBodyId(root->FirstChildElement(TAG_BODY)));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
    data.setCritical(readCriticalChance(root->FirstChildElement(TAG_CRITICAL_CHANCE)));
    data.setAnimation(readAnimation(root->FirstChildElement(TAG_ANIMATION)));
    data.setSpeed(readProjectileSpeed(root->FirstChildElement(TAG_SPEED)));
    data.setTerrainCollide(readTerrainCollide(root->FirstChildElement(TAG_COLLIDE_TERRAIN)));
    data.setGravityScale(readProjectileGravityScale(root->FirstChildElement(TAG_GRAVITY_SCALE)));
    data.setAnimationLayerIndex(readAnimationLayerIndex(root->FirstChildElement(TAG_ANIMATION_LAYER)));

    return data;
}