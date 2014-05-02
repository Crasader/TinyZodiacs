//
//  MonsterFactoryDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/29/14.
//
//

#ifndef __TinyZodiacs__MonsterFactoryDTO__
#define __TinyZodiacs__MonsterFactoryDTO__

#include <iostream>
#include "cocos2d.h"
#include "PhysicConstants.h"

USING_NS_CC;

class MonsterFactoryDTO: public CCObject {

private:
protected:
public:
    MonsterFactoryDTO();
    virtual ~MonsterFactoryDTO();
    
    virtual bool init();
    
    Group group;
    CCArray* listMonsterCreatorDTO;
    
    
    
    CREATE_FUNC(MonsterFactoryDTO);
};

#endif /* defined(__TinyZodiacs__MonsterFactoryDTO__) */
