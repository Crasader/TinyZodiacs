//
//  XMLHeroParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "XMLHeroParser.h"
#include "XMLCharacterParser.h"

#define TAG_HERO "hero"
#define ATTRIBUTE_HERO_LOCKED "locked"
#define ATTRIBUTE_HERO_ID "id"
#define ATTRIBUTE_HERO_BUTTON_ID "button_id"

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
    int locked = XMLHelper::readAttributeBool(heroPreviewDTOXMLElement, ATTRIBUTE_HERO_LOCKED, true);
    string buttonID = XMLHelper::readAttributeString(heroPreviewDTOXMLElement, ATTRIBUTE_HERO_BUTTON_ID, "");
    
    heroPreviewDTO->id = id;
    heroPreviewDTO->locked = locked;
    heroPreviewDTO->buttonID = buttonID;
    
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

