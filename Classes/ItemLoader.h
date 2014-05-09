//
//  ItemLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__ItemLoader__
#define __TinyZodiacs__ItemLoader__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "DataCollector.h"
#include "XMLItemParser.h"

using namespace tinyxml2;

#define TAG_ITEM "item"

class ItemLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
};

#endif /* defined(__TinyZodiacs__ItemLoader__) */
