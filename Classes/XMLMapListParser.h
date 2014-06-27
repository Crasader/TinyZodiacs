//
//  XMLMapListParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#ifndef __TinyZodiacs__XMLMapListParser__
#define __TinyZodiacs__XMLMapListParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "MapSelectData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLMapListParser
{
private:
protected:
    static std::string readID(const XMLElement* root);
    static std::string readNormalIcon(const XMLElement* root);
    static std::string readSelectedIcon(const XMLElement* root);
    static bool readState(const XMLElement* root);
    
    //    static std::vector<MapSelectData> parseData(const XMLElement* root);
    static std::vector<MapSelectData> loadXMLFile(const char *xmlFileName);
public:
    static std::vector<MapSelectData> getMapList();
};

#endif /* defined(__TinyZodiacs__XMLMapListParser__) */
