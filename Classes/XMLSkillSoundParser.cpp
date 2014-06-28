//
//  XMLSkillSoundParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#include "XMLSkillSoundParser.h"
#define TAG_EXCUTE_SOUND "excute"
#define TAG_HIT_SOUND "hit"
#define TAG_STOP_SOUND "stop"

std::string XMLSkillSoundParser::readExcuteSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";}

std::string XMLSkillSoundParser::readHitSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLSkillSoundParser::readStopSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

SkillSoundData XMLSkillSoundParser::loadData(const XMLElement* root)
{
    SkillSoundData data;
    data.setExcuteSoundStr(readExcuteSoundString(root->FirstChildElement(TAG_EXCUTE_SOUND)));
    data.setHitSoundStr(readHitSoundString(root->FirstChildElement(TAG_HIT_SOUND)));
    data.setStopSoundStr(readStopSoundString(root->FirstChildElement(TAG_STOP_SOUND)));
    
    return data;
}