//
//  XMLItemSoundParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#include "XMLItemSoundParser.h"

#define TAG_APPEAR "appear"
#define TAG_DISAPPEAR "disappear"
#define TAG_DESTROY "destroy"
#define TAG_CONSUME "consume"

std::string XMLItemSoundParser::readAppearSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLItemSoundParser::readDisappearSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLItemSoundParser::readDestroySoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLItemSoundParser::readConsumeSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

ItemSoundData XMLItemSoundParser::loadData(const XMLElement* root)
{
    ItemSoundData data;
    data.setAppearSoundStr(readAppearSoundString(root->FirstChildElement(TAG_APPEAR)));
    data.setDestroySoundStr(readDestroySoundString(root->FirstChildElement(TAG_DESTROY)));
    data.setDisappearSoundStr(readDisappearSoundString(root->FirstChildElement(TAG_DISAPPEAR)));
    data.setConsumeSoundStr(readConsumeSoundString(root->FirstChildElement(TAG_CONSUME)));

    return data;
}