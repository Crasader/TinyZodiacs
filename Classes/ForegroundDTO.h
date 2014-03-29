//
//  ForegroundDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#ifndef __TinyZodiacs__ForegroundDTO__
#define __TinyZodiacs__ForegroundDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ForegroundDTO: public CCObject
{
public:
    ForegroundDTO();
    virtual ~ForegroundDTO();
    virtual bool init();
    
    std::string imageName;
    float ratioX;
    float ratioY;
    float positionX;
    float positionY;
    int layerIndex;
    
    CREATE_FUNC(ForegroundDTO);
};


#endif /* defined(__TinyZodiacs__ForegroundDTO__) */
