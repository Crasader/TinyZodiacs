//
//  TowerDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/26/14.
//
//

#ifndef __TinyZodiacs__TowerDTO__
#define __TinyZodiacs__TowerDTO__

#include <iostream>

#include "cocos2d.h"
#include "GameObject.h"

using namespace std;
USING_NS_CC;

class TowerDTO: public CCObject
{
public:
    TowerDTO();
    virtual ~TowerDTO();
    
    virtual bool init();
    
    string id;
    string group;
    float x;
    float y;
    
    CREATE_FUNC(TowerDTO);
};


#endif /* defined(__TinyZodiacs__TowerDTO__) */
