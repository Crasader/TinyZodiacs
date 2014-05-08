//
//  ItemLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "ItemLoader.h"

bool ItemLoader::loadData()
{
    loadDataByFileName("item_list.xml");
    
    return true;
}

bool ItemLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    for (XMLElement* element = docElement->FirstChildElement(TAG_ITEM); element;
         element = element->NextSiblingElement())
    {
        ItemDTO* itemDTO = XMLItemParser::getItemDTOFromXMLElement(element);
        
        DataCollector::getInstance()->setItemDTO(itemDTO->id.c_str(), itemDTO);
    }
    
    delete document;
    return true;
}
