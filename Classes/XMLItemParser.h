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

#define ATTRIBUTE_ITEM_ID "id"
#define ATTRIBUTE_ITEM_IMAGE_NAME "image_name"
#define ATTRIBUTE_ITEM_BODY_NAME "body_name"
#define ATTRIBUTE_ITEM_LIFE_TIME "life_time"


using namespace tinyxml2;

class XMLItemParser
{
private:
protected:
public:
    static ItemDTO* getItemDTOFromXMLElement(XMLElement* xmlElement);
    
};

#endif /* defined(__TinyZodiacs__XMLItemParser__) */
