//
//  XMLAffectSoundParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#include "XMLAffectSoundParser.h"
std::string XMLAffectSoundParser::readSoundString(const XMLElement* root)
{
    if(root != NULL)
    {
        return XMLHelper::readString(root, "");
    }
    return "";
}

std::string XMLAffectSoundParser::loadData(const XMLElement* root)
{
    std::string data;
    data = readSoundString(root);
    return data;
}