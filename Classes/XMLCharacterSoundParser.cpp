//
//  XMLCharacterSoundParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/4/14.
//
//

#include "XMLCharacterSoundParser.h"

#define TAG_HURT_SOUND "hurt"
#define TAG_JUMP_SOUND "jump"
#define TAG_DEATH_SOUND "death"


CharacterSoundData XMLCharacterSoundParser::loadData(const XMLElement* root)
{
    CharacterSoundData data;
    data.setJumpSoundStr(readJumpSoundString(root->FirstChildElement(TAG_JUMP_SOUND)));
    data.setHurtSoundStr(readHurtSoundString(root->FirstChildElement(TAG_HURT_SOUND)));
    data.setDeathSoundStr(readDeathSoundString(root->FirstChildElement(TAG_DEATH_SOUND)));

//    CCLOG("%s",data.getDeathSoundStr().c_str());
//    CCLOG("%s",data.getHurtSoundStr().c_str());
//    CCLOG("%s",data.getJumpSoundStr().c_str());

    
    return data;
}

 std::string XMLCharacterSoundParser::readHurtSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

 std::string XMLCharacterSoundParser::readDeathSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

 std::string XMLCharacterSoundParser::readJumpSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

