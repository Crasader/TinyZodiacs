//
//  XMLHelper.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/17/14.
//
//

#include "XMLHelper.h"

XMLDocument* XMLHelper::getXMLDocument (const char *xmlFileName)
{
    XMLDocument* document = new XMLDocument();
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    if (!pFileData)
    {
        CCLOG("Empty file: %s", fullPath.c_str());
        assert(0);
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    
    if( document->Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        assert(0);
    }
    delete []pFileData;
    
    return document;
}

std::string XMLHelper::readString(const XMLElement* root, std::string defaultValue)
{
    if(root != NULL)
    {
        std::string value =CCString::createWithFormat("%s",root->GetText())->getCString() ;
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
        if(root->Attribute(attributeName) == NULL)
        {
            return defaultValue;
        }
        std::string textValue = root->Attribute(attributeName);
        return textValue;
    }
    return defaultValue;
}

int  XMLHelper::readAttributeInt(const XMLElement* root, const char* attributeName, int defaultValue)
{
    if(root != NULL)
    {
        if(root->Attribute(attributeName) == NULL)
        {
            return defaultValue;
        }
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
        if(root->Attribute(attributeName) == NULL)
        {
            return defaultValue;
        }
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
        if(root->Attribute(attributeName) == NULL)
        {
            return defaultValue;
        }
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
bool  XMLHelper::readAttributeBoolString(const XMLElement* root, const char* attributeName, bool defaultValue)
{
    if(root != NULL)
    {
        if(root->Attribute(attributeName) == NULL)
        {
            return defaultValue;
        }
        std::string textValue = root->Attribute(attributeName);
        
        if(strcasecmp(textValue.c_str(), "true") == 0)
        {
            return true;
        }
        else if(strcasecmp(textValue.c_str(), "false") == 0)
        {
            return false;
        }
        else
        {
            return defaultValue;
        }
    }
    return defaultValue;
}

const XMLElement* XMLHelper::loadElementById(const char* tagName, const char* key, const char* attributeName, const XMLElement* root)
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
