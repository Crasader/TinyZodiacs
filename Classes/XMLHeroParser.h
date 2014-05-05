//
//  XMLHeroParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__XMLHeroParser__
#define __TinyZodiacs__XMLHeroParser__

#include <iostream>
#include "cocos2d.h"
#include "HeroDTO.h"

using namespace tinyxml2;

class XMLHeroParser
{
private:
protected:
public:
    static HeroDTO* getHeroDTOFromXMLElement(XMLElement* heroXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLHeroParser__) */
