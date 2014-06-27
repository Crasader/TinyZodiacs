//
//  XMLItemParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__XMLItemParser__
#define __TinyZodiacs__XMLItemParser__

#include <iostream>
#include "cocos2d.h"
#include "ItemDTO.h"
#include "Constants.h"
#include "XMLHelper.h"
#include "Affect.h"



using namespace tinyxml2;
using namespace std;

class XMLItemParser
{
private:
protected:
public:
    static CCArray* getItemDTOListFromXMLElement(XMLElement* xmlElement);
    static ItemDTO* getItemDTOFromXMLElement(XMLElement* xmlElement);
    static ItemStruct getSubItemStructFromXMLElement(XMLElement* xmlElement);
    static vector<ItemStruct> getSubItemStructListFromXMLElement(XMLElement* xmlElement);
    static vector<string> getAffectListFromXMLElement(XMLElement* xmlElement);
};

#endif /* defined(__TinyZodiacs__XMLItemParser__) */
