//
//  MonsterLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__MonsterLoader__
#define __TinyZodiacs__MonsterLoader__

#include <iostream>
#include "cocos2d.h"
#include "HeroDTO.h"
#include "XMLMonsterParser.h"
#include "DataCollector.h"
#include "XMLHelper.h"

using namespace tinyxml2;
USING_NS_CC;

class MonsterLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
};

#endif /* defined(__TinyZodiacs__MonsterLoader__) */
