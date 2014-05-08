//
//  MonsterDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__MonsterDTO__
#define __TinyZodiacs__MonsterDTO__

#include <iostream>
#include "cocos2d.h"
#include "CharacterDTO.h"
#include "Constants.h"

USING_NS_CC;

class MonsterDTO: public CharacterDTO
{
private:
protected:
public:
    MonsterDTO();
    ~MonsterDTO();
    
    string sensorBody;
    
    vector<ItemStruct> listItem;
    
    CREATE_FUNC(MonsterDTO);
};

#endif /* defined(__TinyZodiacs__MonsterDTO__) */
