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

#define TAG_MAP "map"

#define ATTRIBUTE_STATE "state"
#define ATTRIBUTE_NORMAL_ICON "normal_icon"
#define ATTRIBUTE_SELECTED_ICON "selected_icon"
#define ATTRIBUTE_ID "id"

class XMLMapListParser
{
private:
protected:
public:
    static std::string readID(const XMLElement* root);
    static std::string readNormalIcon(const XMLElement* root);
    static std::string readSelectedIcon(const XMLElement* root);
    static bool readState(const XMLElement* root);
    
//    static std::vector<MapSelectData> parseData(const XMLElement* root);
    static std::vector<MapSelectData> loadXMLFile(const char *xmlFileName);
    
    static std::vector<MapSelectData> getMapList();
};

#endif /* defined(__TinyZodiacs__XMLMapListParser__) */
