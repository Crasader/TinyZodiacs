//
//  XMLHelper.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/17/14.
//
//

#include "XMLHelper.h"

std::string XMLHelper::readString(const XMLElement* root, std::string defaultValue)
{
    if(root != NULL)
    {
        std::string value = root->GetText();
        return value;
    }
    return defaultValue;
}

int XMLHelper::readInt(const XMLElement* root, int defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->GetText();
        int value = atoi(textValue.c_str());
        return value;
    }
    return defaultValue;
}

float XMLHelper::readFloat(const XMLElement* root, float defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->GetText();
        float value = atof(textValue.c_str());
        return value;
    }
    return defaultValue;
}

bool XMLHelper::readBool(const XMLElement* root, bool defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->GetText();
        int value = atoi(textValue.c_str());
        if(value == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return defaultValue;
}

std::string  XMLHelper::readAttributeString(const XMLElement* root, const char* attributeName, std::string defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->Attribute(attributeName);
        return textValue;
    }
    return defaultValue;
}

int  XMLHelper::readAttributeInt(const XMLElement* root, const char* attributeName, int defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->Attribute(attributeName);
        int value = atoi(textValue.c_str());
        return value;
    }
    return defaultValue;
}

float  XMLHelper::readAttributeFloat(const XMLElement* root, const char* attributeName, float defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->Attribute(attributeName);
        float value = atof(textValue.c_str());
        return value;
    }
    return defaultValue;
}

bool  XMLHelper::readAttributeBool(const XMLElement* root, const char* attributeName, bool defaultValue)
{
    if(root != NULL)
    {
        std::string textValue = root->Attribute(attributeName);
        int value = atoi(textValue.c_str());
        if(value == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return defaultValue;
}

const XMLElement* XMLHelper::loadElementById(const char* tagName,const char* key, const char* attributeName, const XMLElement* root)
{
    const XMLElement* child = root->FirstChildElement(tagName);
    
    while(child != NULL)
    {
//        CCString* temp1 = CCString::createWithFormat("%s",key);
//        CCString* temp2 = CCString::createWithFormat("%s",child->Attribute(attributeName));
        std::string temp1 = key;
        std::string temp2 = child->Attribute(attributeName);
        
        if(temp1 == temp2)
        {
            return  child;
        }
        child = child->NextSiblingElement();
    }
    return NULL;
}
