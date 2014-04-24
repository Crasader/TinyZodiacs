//
//  MapFactory.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/18/14.
//
//

#ifndef __TinyZodiacs__MapFactory__
#define __TinyZodiacs__MapFactory__

#include <iostream>
#include "cocos2d.h"
#include "MapDTO.h"
#include "XMLMapParser.h"

USING_NS_CC;

class MapFactory
{
private:
    MapFactory();
    cocos2d::CCDictionary* mapDTODictionary;
public:
    virtual ~MapFactory();
    
    static MapFactory* getSharedFactory();
    bool loadXMLMap();
    bool loadXMLMapByNameFile(const char *xmlFileName);
    MapDTO* getMapByName(const char* mapName);

};


#endif /* defined(__TinyZodiacs__MapFactory__) */
