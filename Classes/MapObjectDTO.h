//
//  MapObjectDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/17/14.
//
//

#ifndef __TinyZodiacs__MapObjectDTO__
#define __TinyZodiacs__MapObjectDTO__

#include <iostream>
#include "Cocos2d.h"

using namespace std;
USING_NS_CC;

class MapObjectDTO: public CCObject
{
public:
    virtual bool init();
    
    
    MapObjectDTO();
    virtual ~MapObjectDTO();
    
    std::string id;
    std::string imageName;
    std::string bodyName;
    float x;
    float y;
    float layerIndex;
    bool canPass;
    CREATE_FUNC(MapObjectDTO);
};

#endif /* defined(__TinyZodiacs__MapObjectDTO__) */
