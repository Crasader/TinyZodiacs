//
//  MonsterCreatorDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/29/14.
//
//

#ifndef __TinyZodiacs__MonsterCreatorDTO__
#define __TinyZodiacs__MonsterCreatorDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MonsterCreatorDTO: public CCObject {
private:
protected:
    
public:
    MonsterCreatorDTO();
    virtual ~MonsterCreatorDTO();
    
    virtual bool init();
    
    float delayPerUnit;
    float delay;
    float positionX;
    float positionY;
    int laneID;
    std::vector<std::string> listMonsterID;
    
    CREATE_FUNC(MonsterCreatorDTO);
};

#endif /* defined(__TinyZodiacs__MonsterCreatorDTO__) */
