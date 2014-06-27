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

class XMLMonsterParser
{
private:
protected:
public:
    static MonsterDTO* getMonsterDTOFromXMLElement(XMLElement* monsterXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLMonsterParser__) */
