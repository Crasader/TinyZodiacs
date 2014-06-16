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

#define TAG_BODY "body"
#define TAG_ANIMATION "animation"
#define TAG_HP "hp"
#define TAG_ATTACK "atk"
#define TAG_DEFENSE "def"
#define TAG_SPEED "speed"
#define TAG_ATTACK_SPEED "atk_speed"
#define TAG_MAX_JUMP "max_jump"
#define TAG_JUMP_HEIGHT "jump_height"
#define TAG_SKILL_0 "skill_0"
#define TAG_SKILL_1 "skill_1"
#define TAG_SKILL_2 "skill_2"
#define ATTRIBUTE_ID "id"

#define TAG_SFX "sfx"


#define TAG_DEFENSE "defense"
#define ATTRIBUTE_DEFENSE_ID "id"
#define ATTRIBUTE_DEFENSE_BUTTON_ID "button_id"
#define ATTRIBUTE_DEFENSE_COST "cost"


#define RUN "-run"
#define ATTACK "-attack"
#define JUMP "-jump"
#define IDLE "-idle"
#define FALL "-fall"
#define FLY "-fly"
#define SKILL "-skill"




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
