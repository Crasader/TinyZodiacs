//
//  MonsterLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "MonsterLoader.h"

bool MonsterLoader::loadData()
{
    loadDataByFileName("monster_onion.xml");
     loadDataByFileName("monster_pig.xml");
    
    return true;
}

bool MonsterLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
  
    XMLElement* docElement = document->FirstChildElement();
    
    MonsterDTO* monsterDTO = XMLMonsterParser::getMonsterDTOFromXMLElement(docElement);
    DataCollector::getInstance()->setMonsterDTO(monsterDTO->id.c_str(), monsterDTO);
    
    delete document;
    return true;
}
