//
//  MapLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "MapLoader.h"
#include "MapDTO.h"
#include "DataCollector.h"
#include "XMLMapParser.h"


bool MapLoader::loadData()
{
    MapLoader::loadDataByFileName("map1.xml");
    
    MapLoader::loadDataByFileName("map2.xml");
    
    return true;
}

bool MapLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    MapDTO* mapDTO = XMLMapParser::getMapDTOFromXMLNode(docElement);
    
    DataCollector::getInstance()->setMapDTO(mapDTO->id.c_str(), mapDTO);

    return true;
}

CCArray* MapLoader::loadDefenseDTOList(const char* fileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(fileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    return XMLCharacterParser::getDefenseDTOListFromXMLElement(docElement);
}
