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
//    if(root != NULL)
//    {
//        string value = root->GetText();
//        return value;
//    }
//    return "";
    return XMLHelper::readString(root, "");
}

float SkillType1Parser::readProjectileSpeed(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string textValue = root->GetText();
//        float value = atof(textValue.c_str());
//        return value;
//    }
//    return 0;
    return XMLHelper::readFloat(root, 0);
}

float SkillType1Parser::readProjectileGravityScale(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string textValue = root->GetText();
//        float value = atof(textValue.c_str());
//        return value;
//    }
//    return 0;
    return XMLHelper::readFloat(root, 0);
}

bool SkillType1Parser::readTerrainCollide(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string textValue = root->GetText();
//        bool value = atoi(textValue.c_str());
//        return value;
//    }
//    return false;
    return XMLHelper::readBool(root, false);
}

bool SkillType1Parser::readPiercing(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string textValue = root->GetText();
//        bool value = atoi(textValue.c_str());
//        return value;
//    }
//    return false;
    return XMLHelper::readBool(root, false);
}

NormalShootingSkillData SkillType1Parser::parse(const XMLElement* root, b2World* world)
{
    NormalShootingSkillData data;
//    data.setDamage(readDamage(root->FirstChildElement(TAG_DAMAGE)));
    data.setCoolDown(readCoolDown(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setLifeTime(readLifeTime(root->FirstChildElement(TAG_LIFE_TIME)));
    data.setProjectileBodyId(readProjectileBodyId(root->FirstChildElement(TAG_BODY)));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
//    data.setCritical(readCriticalChance(root->FirstChildElement(TAG_CRITICAL_CHANCE)));
    data.setAnimation(readAnimation(root->FirstChildElement(TAG_ANIMATION)));
    data.setSpeedX(readProjectileSpeed(root->FirstChildElement(TAG_SPEED)->FirstChildElement(TAG_X)));
    data.setSpeedY(readProjectileSpeed(root->FirstChildElement(TAG_SPEED)->FirstChildElement(TAG_Y)));
    data.setTerrainCollide(readTerrainCollide(root->FirstChildElement(TAG_COLLIDE_TERRAIN)));
    data.setGravityScale(readProjectileGravityScale(root->FirstChildElement(TAG_GRAVITY_SCALE)));
    data.setAnimationLayerIndex(readAnimationLayerIndex(root->FirstChildElement(TAG_ANIMATION_LAYER)));
    data.setPiercing(readPiercing(root->FirstChildElement(TAG_PIERCING)));
    data.setTarget(readTarget(root->FirstChildElement(TAG_TARGET)));
    
    if(root->FirstChildElement(TAG_LIST_EFFECT) != NULL)
    {
        //        CCLOG("\t %s","AFFECT ENEMY");
        data.setListEnemyEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ENEMY)));
        //        if(data.getListEnemyEffect() != NULL)
        //        {
        //            CCLOG("%d",data.getListEnemyEffect()->count());
        //        }
        //        CCLOG("\t %s","AFFECT ALLIES");
        data.setListAlliesEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ALLIES)));
        //        if(data.getListAlliesEffect() != NULL)
        //        {
        //            CCLOG("%d",data.getListAlliesEffect()->count());
        //        }
        data.setListSelfEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_SELF)));
    }

    return data;
}