//
//  XMLTowerParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/10/14.
//
//

#include "XMLTowerParser.h"

std::string XMLTowerParser::readSensorBody(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

TowerDTO* XMLTowerParser::getTowerDTOFromXMLElement(XMLElement* towerXMLElement)
{
    TowerDTO* towerDTO = TowerDTO::create();
    XMLCharacterParser::getCharacterDTOFromXMLElement(towerDTO, towerXMLElement);
    towerDTO->towerSensorId = readSensorBody(towerXMLElement->FirstChildElement(TAG_TOWER_SENSOR));
    return towerDTO;
}