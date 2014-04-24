//
//  MapDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/17/14.
//
//

#ifndef __TinyZodiacs__MapDTO__
#define __TinyZodiacs__MapDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MapDTO: public CCObject
{
public:
    MapDTO();
    virtual ~MapDTO();
    virtual bool init();
    
    string id;
    float width;
    float height;
    
    
    CCArray* listMapObjectDTO;
    CCArray* listBackgroundDTO;
    CCArray* listForegroundDTO;
    CCArray* listSensorObjectDTO;

    
    CREATE_FUNC(MapDTO);
};

#endif /* defined(__TinyZodiacs__MapDTO__) */
