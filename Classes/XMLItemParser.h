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

#define TAG_ITEM "item"
#define ATTRIBUTE_ITEM_ID "id"
#define ATTRIBUTE_ITEM_TYPE "type"
#define ATTRIBUTE_ITEM_IMAGE_NAME "image_name"
#define ATTRIBUTE_ITEM_BODY_NAME "body_name"
#define ATTRIBUTE_ITEM_LIFE_TIME "life_time"
#define TAG_SUB_ITEM_LIST "item_list"
#define TAG_ITEM_AFFECT_LIST "affect_list"
#define TAG_ITEM_AFFECT "affect"
#define ATTRIBUTE_ITEM_CHANCE "chance"
#define ATTRIBUTE_ITEM_ANIMATION "animation"
#define ATTRIBUTE_ITEM_AFFECT_ID "id"

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
