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
    
    CCArray* listItemDTO = XMLItemParser::getItemDTOListFromXMLElement(docElement);
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(listItemDTO, object)
    {
        ItemDTO* itemDTO = static_cast<ItemDTO*>(object);
        DataCollector::getInstance()->setItemDTO(itemDTO->id.c_str(), itemDTO);
    }
    
    delete document;
    return true;
}
