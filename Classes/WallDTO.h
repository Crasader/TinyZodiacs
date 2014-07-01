//
//  WallDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#ifndef __TinyZodiacs__WallDTO__
#define __TinyZodiacs__WallDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class WallDTO: public CCObject
{
private:
protected:
public:
    WallDTO();
    ~WallDTO();
    
    virtual bool init();
    
    float x;
    float y;
    float edge_x;
    float edge_y;
    bool deadWall;
    
    CREATE_FUNC(WallDTO);
};

#endif /* defined(__TinyZodiacs__WallDTO__) */
