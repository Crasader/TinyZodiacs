//
//  WaveDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/21/14.
//
//

#ifndef __TinyZodiacs__WaveDTO__
#define __TinyZodiacs__WaveDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class WaveDTO: public CCObject
{
public:
    WaveDTO();
    virtual ~WaveDTO();
    virtual bool init();

    CCArray* listMonsterFactoryDTO;
    CCArray* listItemCreatorDTO;
    
    CREATE_FUNC(WaveDTO);
};
#endif /* defined(__TinyZodiacs__WaveDTO__) */
