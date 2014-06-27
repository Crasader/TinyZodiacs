//
//  XMLCharacterParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__XMLCharacterParser__
#define __TinyZodiacs__XMLCharacterParser__

#include <iostream>
#include "cocos2d.h"
#include "CharacterDTO.h"
#include "XMLHelper.h"
#include "DefenseDTO.h"

using namespace tinyxml2;

class XMLCharacterParser
{
private:
protected:
    static string readBodyData(tinyxml2::XMLElement* root);
    static int readHealthData(tinyxml2::XMLElement* root);
    static int readAttackData(tinyxml2::XMLElement* root);
    static int readDefenseData(tinyxml2::XMLElement* root);
    static float readSpeedData(tinyxml2::XMLElement* root);
    static float readAttackSpeedData(tinyxml2::XMLElement* root);
    static int readMaxJumpData(tinyxml2::XMLElement* root);
    static float readJumpHeightData(tinyxml2::XMLElement* root);
    static string readAnimationData(tinyxml2::XMLElement* root);
    static string readSkill(tinyxml2::XMLElement* root);
    static string readSoundData(tinyxml2::XMLElement* root);
public:
    static CharacterDTO* getCharacterDTOFromXMLElement(XMLElement* characterElement);
    static void getCharacterDTOFromXMLElement(CharacterDTO* characterDTO, XMLElement* characterElement);
    
    static DefenseDTO* getDefenseDTOFromXMLElement(XMLElement* defenseElement);
     static CCArray* getDefenseDTOListFromXMLElement(XMLElement* defenseListElement);
};

#endif /* defined(__TinyZodiacs__XMLCharacterParser__) */
