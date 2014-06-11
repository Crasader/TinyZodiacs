//
//  XMLCharacterParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#include "XMLCharacterParser.h"
#include "CharacterSoundFactory.h"


string XMLCharacterParser::readSoundData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

string XMLCharacterParser::readBodyData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

string XMLCharacterParser::readAnimationData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

int XMLCharacterParser::readHealthData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int XMLCharacterParser::readAttackData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

string XMLCharacterParser::readSkill(tinyxml2::XMLElement *root)
{
    return XMLHelper::readString(root, "");
}

int XMLCharacterParser::readDefenseData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

float XMLCharacterParser::readSpeedData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

float XMLCharacterParser::readAttackSpeedData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

int XMLCharacterParser::readMaxJumpData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

float XMLCharacterParser::readJumpHeightData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

CharacterDTO* XMLCharacterParser::getCharacterDTOFromXMLElement(XMLElement* characterElement)
{
    CharacterDTO* data = CharacterDTO::create();
    
    data->id = XMLHelper::readAttributeString(characterElement,ATTRIBUTE_ID, "");
    data->body = readBodyData(characterElement->FirstChildElement(TAG_BODY));
    data->animation = readAnimationData(characterElement->FirstChildElement(TAG_ANIMATION));
    data->data.setAttack(readAttackData(characterElement->FirstChildElement(TAG_ATTACK)));
    data->data.setHealth(readHealthData(characterElement->FirstChildElement(TAG_HP)));
    data->data.setDefense(readDefenseData(characterElement->FirstChildElement(TAG_DEFENSE)));
    data->data.setSpeed(readSpeedData(characterElement->FirstChildElement(TAG_SPEED)));
    data->data.setAttackSpeed(readAttackSpeedData(characterElement->FirstChildElement(TAG_ATTACK_SPEED)));
    data->data.setMaxJumpTimes(readMaxJumpData(characterElement->FirstChildElement(TAG_MAX_JUMP)));
    data->data.setJumpHeight(readJumpHeightData(characterElement->FirstChildElement(TAG_JUMP_HEIGHT)));
    data->data.setSkill0(readSkill(characterElement->FirstChildElement(TAG_SKILL_0)));
    data->data.setSkill1(readSkill(characterElement->FirstChildElement(TAG_SKILL_1)));
    data->data.setSkill2(readSkill(characterElement->FirstChildElement(TAG_SKILL_2)));
    data->soundId = readSoundData(characterElement->FirstChildElement(TAG_SFX));
    
    return data;
}

void XMLCharacterParser::getCharacterDTOFromXMLElement(CharacterDTO* characterDTO, XMLElement* characterElement)
{
    characterDTO->id = XMLHelper::readAttributeString(characterElement,ATTRIBUTE_ID, "");
    characterDTO->body = readBodyData(characterElement->FirstChildElement(TAG_BODY));
    characterDTO->animation = readAnimationData(characterElement->FirstChildElement(TAG_ANIMATION));
    characterDTO->data.setAttack(readAttackData(characterElement->FirstChildElement(TAG_ATTACK)));
    characterDTO->data.setHealth(readHealthData(characterElement->FirstChildElement(TAG_HP)));
    characterDTO->data.setDefense(readDefenseData(characterElement->FirstChildElement(TAG_DEFENSE)));
    characterDTO->data.setSpeed(readSpeedData(characterElement->FirstChildElement(TAG_SPEED)));
    characterDTO->data.setAttackSpeed(readAttackSpeedData(characterElement->FirstChildElement(TAG_ATTACK_SPEED)));
    characterDTO->data.setMaxJumpTimes(readMaxJumpData(characterElement->FirstChildElement(TAG_MAX_JUMP)));
    characterDTO->data.setJumpHeight(readJumpHeightData(characterElement->FirstChildElement(TAG_JUMP_HEIGHT)));
    characterDTO->data.setSkill0(readSkill(characterElement->FirstChildElement(TAG_SKILL_0)));
    characterDTO->data.setSkill1(readSkill(characterElement->FirstChildElement(TAG_SKILL_1)));
    characterDTO->data.setSkill2(readSkill(characterElement->FirstChildElement(TAG_SKILL_2)));
    characterDTO->soundId = readSoundData(characterElement->FirstChildElement(TAG_SFX));
}

DefenseDTO* XMLCharacterParser::getDefenseDTOFromXMLElement(XMLElement* defenseElement)
{
    DefenseDTO* defenseDTO = DefenseDTO::create();
    
    string id = XMLHelper::readAttributeString(defenseElement, ATTRIBUTE_DEFENSE_ID,"");
    string icon = XMLHelper::readAttributeString(defenseElement, ATTRIBUTE_DEFENSE_ICON,"");
    int cost = XMLHelper::readAttributeInt(defenseElement, ATTRIBUTE_DEFENSE_COST, 0);
    
    defenseDTO->id = id;
    defenseDTO->icon = icon;
    defenseDTO->cost = cost;
    
    return defenseDTO;
}


CCArray* XMLCharacterParser::getDefenseDTOListFromXMLElement(XMLElement* defenseListElement)
{
    CCArray* arr = CCArray::create();
    
    for (XMLElement* element = defenseListElement->FirstChildElement(TAG_DEFENSE); element; element = element->NextSiblingElement())
    {
        arr->addObject(XMLCharacterParser::getDefenseDTOFromXMLElement(element));
    }
    
    return arr;
}