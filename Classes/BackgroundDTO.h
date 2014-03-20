//
//  BackgroundDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/19/14.
//
//

#ifndef __TinyZodiacs__BackgroundDTO__
#define __TinyZodiacs__BackgroundDTO__

#include <iostream>
#include "Cocos2d.h"

using namespace std;

USING_NS_CC;

class BackgroundDTO: public CCObject
{
public:
    BackgroundDTO();
    virtual ~BackgroundDTO();
    virtual bool init();
    
    std::string imageName;
    std::string spritesheetName;
    float ratioX;
    float ratioY;
    int orderIndex;
    
    CREATE_FUNC(BackgroundDTO);
};


#endif /* defined(__TinyZodiacs__BackgroundDTO__) */
