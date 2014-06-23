//
//  XMLItemParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "XMLItemParser.h"

CCArray* XMLItemParser::getItemDTOListFromXMLElement(XMLElement* xmlElement)
{
    CCArray* listItemDTO = CCArray::create();
    for (XMLElement* element = xmlElement->FirstChildElement(TAG_ITEM); element;
         element = element->NextSiblingElement())
    {
        listItemDTO->addObject(getItemDTOFromXMLElement(element));
    }
    return listItemDTO;
}

ItemDTO* XMLItemParser::getItemDTOFromXMLElement(XMLElement* xmlElement)
{
    ItemDTO* item = ItemDTO::create();
    
    string id = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_ITEM_ID, "");
    string type = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_ITEM_TYPE, "");
    string imageName = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_ITEM_IMAGE_NAME, "");
    string bodyName = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_ITEM_BODY_NAME, "");
    string animation = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_ITEM_ANIMATION,"");
    float lifeTime = XMLHelper::readAttributeFloat(xmlElement, ATTRIBUTE_ITEM_LIFE_TIME, 0);
    int goldValue = XMLHelper::readInt(xmlElement->FirstChildElement(TAG_ITEM_GOLD_VALUE), 0);
    string titleNotification = XMLHelper::readString(xmlElement->FirstChildElement(TAG_ITEM_TITLE_NOTIFICATION), "");
    
    item->id = id;
    item->type = type;
    item->imageName = imageName;
    item->bodyName = bodyName;
    item->animation = animation;
    item->lifeTime = lifeTime;
    item->listSubItemStruct = getSubItemStructListFromXMLElement(xmlElement);
    item->listAffectID = getAffectListFromXMLElement(xmlElement);
    item->goldValue = goldValue;
    item->titleNotification = titleNotification;
    
    return item;
}

ItemStruct XMLItemParser::getSubItemStructFromXMLElement(XMLElement* xmlElement)
{
    ItemStruct itemStruct;
    itemStruct.itemID = xmlElement->Attribute(ATTRIBUTE_ITEM_ID);
    itemStruct.chance = atof(xmlElement->Attribute(ATTRIBUTE_ITEM_CHANCE));
    return itemStruct;
}

vector<ItemStruct> XMLItemParser::getSubItemStructListFromXMLElement(XMLElement* xmlElement)
{
    vector<ItemStruct> listItemStruct;
    XMLElement* listSubItemStructXMLElement = xmlElement->FirstChildElement(TAG_SUB_ITEM_LIST);
    if(listSubItemStructXMLElement != NULL)
    {
        for (XMLElement* element = listSubItemStructXMLElement->FirstChildElement(TAG_ITEM); element;
             element = element->NextSiblingElement())
        {
            listItemStruct.push_back(getSubItemStructFromXMLElement(element));
        }
    }
    return listItemStruct;
}

vector<string> XMLItemParser::getAffectListFromXMLElement(XMLElement* xmlElement)
{
    vector<string> listAffectID;
    
    XMLElement* listAffectListXMLElement = xmlElement->FirstChildElement(TAG_ITEM_AFFECT_LIST);
    if(listAffectListXMLElement != NULL)
    {
        for (XMLElement* element = listAffectListXMLElement->FirstChildElement(TAG_ITEM_AFFECT); element;
             element = element->NextSiblingElement())
        {
            listAffectID.push_back(XMLHelper::readAttributeString(element, ATTRIBUTE_ITEM_AFFECT_ID, ""));
        }
    }
    return listAffectID;
}
