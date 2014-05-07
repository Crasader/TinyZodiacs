//
//  XMLMonsterParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "XMLMonsterParser.h"

MonsterDTO* XMLMonsterParser::getMonsterDTOFromXMLElement(XMLElement* heroXMLElement)
{
    MonsterDTO* monsterDTO = MonsterDTO::create();
    XMLCharacterParser::getCharacterDTOFromXMLElement(monsterDTO, heroXMLElement);
    
    monsterDTO->sensorBody = XMLHelper::readString(heroXMLElement->FirstChildElement(TAG_SENSOR_BODY), "");
    
    return monsterDTO;
}