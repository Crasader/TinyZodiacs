//
//  SensorObjectDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/22/14.
//
//

#ifndef __TinyZodiacs__SensorObjectDTO__
#define __TinyZodiacs__SensorObjectDTO__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

using namespace std;
USING_NS_CC;

class SensorObjectDTO: public CCObject
{
public:
    SensorObjectDTO();
    virtual ~SensorObjectDTO();
    
    virtual bool init();
    
    float jumpHeight;
    float moveSpeed;
    bool mustStop;
    bool isBack;
    Direction direction;
    float x;
    float y;
    float edge_x;
    float edge_y;
    vector<int> listLaneID;
    
    CREATE_FUNC(SensorObjectDTO);
};

#endif /* defined(__TinyZodiacs__SensorObjectDTO__) */
