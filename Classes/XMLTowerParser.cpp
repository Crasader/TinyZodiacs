//
//  XMLTowerParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/10/14.
//
//

#include "XMLTowerParser.h"

TowerDTO* XMLTowerParser::getTowerDTOFromXMLElement(XMLElement* towerXMLElement)
{
    TowerDTO* towerDTO = TowerDTO::create();
    XMLCharacterParser::getCharacterDTOFromXMLElement(towerDTO, towerXMLElement);
    return towerDTO;
}