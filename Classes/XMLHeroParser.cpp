//
//  XMLHeroParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "XMLHeroParser.h"
#include "XMLCharacterParser.h"

HeroDTO* XMLHeroParser::getHeroDTOFromXMLElement(XMLElement* heroXMLElement)
{
    HeroDTO* heroDTO = HeroDTO::create();
    XMLCharacterParser::getCharacterDTOFromXMLElement(heroDTO, heroXMLElement);
    return heroDTO;
}