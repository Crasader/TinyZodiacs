//
//  XMLProjectileSoundParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/24/14.
//
//

#include "XMLProjectileSoundParser.h"

#define TAG_CREATE_SOUND "create"
#define TAG_HIT_SOUND "hit"
#define TAG_SHOOT_SOUND "shoot"
#define TAG_DIE_SOUND "die"


std::string XMLProjectileSoundParser::readCreateSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";}

std::string XMLProjectileSoundParser::readShootSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLProjectileSoundParser::readHitSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLProjectileSoundParser::readDieSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

ProjectileSoundData XMLProjectileSoundParser::loadData(const XMLElement* root)
{
    ProjectileSoundData data;
    data.setCreateSoundStr(readCreateSoundString(root->FirstChildElement(TAG_CREATE_SOUND)));
    data.setShootSoundStr(readShootSoundString(root->FirstChildElement(TAG_SHOOT_SOUND)));
    data.setDieSoundStr(readDieSoundString(root->FirstChildElement(TAG_DIE_SOUND)));
    data.setHitSoundStr(readHitSoundString(root->FirstChildElement(TAG_HIT_SOUND)));
    
    return data;
}