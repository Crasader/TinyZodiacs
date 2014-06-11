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

HeroPreviewDTO* XMLHeroParser::getHeroPreviewDTOXMLElement(XMLElement* heroPreviewDTOXMLElement)
{
    HeroPreviewDTO* heroPreviewDTO = HeroPreviewDTO::create();
    
    string id = XMLHelper::readAttributeString(heroPreviewDTOXMLElement, ATTRIBUTE_HERO_ID, "");
    int state = XMLHelper::readAttributeInt(heroPreviewDTOXMLElement, ATTRIBUTE_HERO_STATE, 0);
    
    heroPreviewDTO->id = id;
    heroPreviewDTO->state = state;
    
    return heroPreviewDTO;
}

CCArray* XMLHeroParser::getHeroPreviewListXMLFromXMLElement(XMLElement* heroPreviewListXMLElement)
{
    CCArray* arr = CCArray::create();
    
    for (XMLElement* element = heroPreviewListXMLElement->FirstChildElement(TAG_HERO); element; element = element->NextSiblingElement())
    {
        arr->addObject(XMLHeroParser::getHeroPreviewDTOXMLElement(element));
    }
    
    return arr;
}

