//
//  XMLSkillAnimationParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 7/1/14.
//
//

#include "XMLSkillAnimationParser.h"
#include "DataCollector.h"

#define TAG_PRE_EXCUTE "pre_excute"
#define TAG_EXCUTE "excute"
#define TAG_PRE_STOP "pre_stop"
#define TAG_STOP "stop"

AnimationObject* XMLSkillAnimationParser::readPreExcuteAnimation(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return NULL;
        }
        AnimationObject* anim = DataCollector::getInstance()->getAnimationObjectByKey(typeValue.c_str());
        return anim;
    }
    return NULL;
}

AnimationObject* XMLSkillAnimationParser::readExcuteAnimation(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return NULL;
        }
        AnimationObject* anim = DataCollector::getInstance()->getAnimationObjectByKey(typeValue.c_str());
        return anim;
    }
    return NULL;
}

AnimationObject* XMLSkillAnimationParser::readPreStopAnimation(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return NULL;
        }
        AnimationObject* anim = DataCollector::getInstance()->getAnimationObjectByKey(typeValue.c_str());
        return anim;
    }
    return NULL;
}

AnimationObject* XMLSkillAnimationParser::readStopAnimation(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return NULL;
        }
        AnimationObject* anim = DataCollector::getInstance()->getAnimationObjectByKey(typeValue.c_str());
        return anim;
    }
    return NULL;
}

SkillAnimationData XMLSkillAnimationParser::loadData(const XMLElement* root)
{
    SkillAnimationData data;
    data.setPreExcuteAnimation(readPreExcuteAnimation(root->FirstChildElement(TAG_PRE_EXCUTE)));
    data.setExcuteAnimation(readExcuteAnimation(root->FirstChildElement(TAG_EXCUTE)));
    data.setPreStopAnimation(readPreStopAnimation(root->FirstChildElement(TAG_PRE_STOP)));
    data.setStopAnimation(readStopAnimation(root->FirstChildElement(TAG_STOP)));
    return data;
}