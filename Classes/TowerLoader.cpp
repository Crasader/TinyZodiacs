//
//  TowerLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/9/14.
//
//

#include "TowerLoader.h"

bool TowerLoader::loadData()
{
    loadDataByFileName("tower_1.xml");
    loadDataByFileName("tower_2.xml");
    loadDataByFileName("tower_3.xml");
    loadDataByFileName("tower_4.xml");
    loadDataByFileName("tower_5.xml");
    loadDataByFileName("tower_6.xml");
    loadDataByFileName("maincrystal.xml");
    
    return true;
}

bool TowerLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    TowerDTO* towerDTO = XMLTowerParser::getTowerDTOFromXMLElement(docElement);
    DataCollector::getInstance()->setTowerDTO(towerDTO->id.c_str(), towerDTO);
    
    delete document;
    return true;
}
