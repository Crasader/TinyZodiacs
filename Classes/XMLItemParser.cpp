//
//  XMLItemParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "XMLItemParser.h"

ItemDTO* XMLItemParser::getItemDTOFromXMLElement(XMLElement* itemXMLElement)
{
    ItemDTO* item = ItemDTO::create();
    
    string id = itemXMLElement->Attribute(ATTRIBUTE_ITEM_ID);
    string imageName = itemXMLElement->Attribute(ATTRIBUTE_ITEM_IMAGE_NAME);
    string bodyName = itemXMLElement->Attribute(ATTRIBUTE_ITEM_BODY_NAME);
    float lifeTime = atof(itemXMLElement->Attribute(ATTRIBUTE_ITEM_LIFE_TIME));
    
    item->id = id;
    item->imageName = imageName;
    item->bodyName = bodyName;
    item->lifeTime = lifeTime;
    
    return item;
}