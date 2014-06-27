//
//  XMLTowerParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/10/14.
//
//

#ifndef __TinyZodiacs__XMLTowerParser__
#define __TinyZodiacs__XMLTowerParser__

#include <iostream>
#include "TowerDTO.h"
#include "XMLCharacterParser.h"
#include "XMLHelper.h"

using namespace tinyxml2;

class XMLTowerParser
{
private:
protected:
    static std::string readSensorBody(tinyxml2::XMLElement* root);
public:
    static TowerDTO* getTowerDTOFromXMLElement(XMLElement* towerXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLTowerParser__) */
