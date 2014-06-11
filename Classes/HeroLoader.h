//
//  HeroLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__HeroLoader__
#define __TinyZodiacs__HeroLoader__

#include <iostream>
#include "cocos2d.h"
#include "HeroDTO.h"
#include "XMLHeroParser.h"
#include "DataCollector.h"
#include "XMLHelper.h"

using namespace tinyxml2;
USING_NS_CC;

class HeroLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
    static CCArray* loadListHero(const char *xmlFileName);
};

#endif /* defined(__TinyZodiacs__HeroLoader__) */
