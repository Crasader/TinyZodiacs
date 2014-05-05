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
//    HeroLoader::loadDataByFileName("monster_cat.xml");
//    HeroLoader::loadDataByFileName("character_monkey.xml");
    
    return true;
}

bool MonsterLoader::loadDataByFileName(const char *xmlFileName)
{
    HeroDTO* data = HeroDTO::create();
    
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
  
    XMLElement* docElement = document->FirstChildElement();
    
    HeroDTO* heroDTO = XMLHeroParser::getHeroDTOFromXMLElement(docElement);
    DataCollector::getInstance()->setHeroDTO(heroDTO->id.c_str(), heroDTO);
    
    delete document;
    return data;
}
