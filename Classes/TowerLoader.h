//
//  TowerLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/9/14.
//
//

#ifndef __TinyZodiacs__TowerLoader__
#define __TinyZodiacs__TowerLoader__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "DataCollector.h"
#include "XMLTowerParser.h"

using namespace tinyxml2;

class TowerLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
};

#endif /* defined(__TinyZodiacs__TowerLoader__) */
