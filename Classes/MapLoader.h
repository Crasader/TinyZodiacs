//
//  MapLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__MapLoader__
#define __TinyZodiacs__MapLoader__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"

using namespace tinyxml2;
USING_NS_CC;

class MapLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
};
#endif /* defined(__TinyZodiacs__MapLoader__) */
