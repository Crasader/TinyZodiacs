//
//  HeroLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "HeroLoader.h"

bool HeroLoader::loadData()
{
    HeroLoader::loadDataByFileName("character_cat.xml");
    HeroLoader::loadDataByFileName("character_monkey.xml");
    
    return true;
}

bool HeroLoader::loadDataByFileName(const char *xmlFileName)
{
    HeroDTO* data = HeroDTO::create();
    
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
  
    XMLElement* docElement = document->FirstChildElement();
    
    HeroDTO* heroDTO = XMLHeroParser::getHeroDTOFromXMLElement(docElement);
    DataCollector::getInstance()->setHeroDTO(heroDTO->id.c_str(), heroDTO);
   
    delete document;
    return data;
}
