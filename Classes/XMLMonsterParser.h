//
//  XMLMonsterParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__XMLMonsterParser__
#define __TinyZodiacs__XMLMonsterParser__

#include <iostream>
#include "MonsterDTO.h"
#include "XMLCharacterParser.h"
#include "XMLHelper.h"

using namespace tinyxml2;

#define TAG_SENSOR_BODY "sensor_body"
#define TAG_MONSTER_ITEM_LIST "item_list"
#define TAG_MONSTER_ITEM "item"
#define ATTRIBUTE_MONSTER_ITEM_ID "id"
#define ATTRIBUTE_MONSTER_ITEM_CHANCE "chance"

class XMLMonsterParser
{
private:
protected:
public:
    static MonsterDTO* getMonsterDTOFromXMLElement(XMLElement* monsterXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLMonsterParser__) */
