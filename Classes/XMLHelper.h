//
//  XMLHelper.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/17/14.
//
//

#ifndef __TinyZodiacs__XMLHelper__
#define __TinyZodiacs__XMLHelper__

#include <iostream>
#include "cocos2d.h"

using namespace tinyxml2;

USING_NS_CC;
class XMLHelper
{
private:
protected:
public:
    static XMLDocument* getXMLDocument (const char *xmlFileName);
    
    static std::string readString(const XMLElement* root, std::string defaultValue);
    static int readInt(const XMLElement* root, int defaultValue);
    static float readFloat(const XMLElement* root, float defaultValue);
    static bool readBool(const XMLElement* root, bool defaultValue);
    
    static std::string readAttributeString(const XMLElement* root, const char* attributeName, std::string defaultValue);
    static int readAttributeInt(const XMLElement* root, const char* attributeName, int defaultValue);
    static float readAttributeFloat(const XMLElement* root, const char* attributeName, float defaultValue);
    static bool readAttributeBool(const XMLElement* root, const char* attributeName, bool defaultValue);
    static const XMLElement* loadElementById(const char* tagName,const char* key, const char* attributeName, const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLHelper__) */
