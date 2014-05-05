//
//  HeroDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/5/14.
//
//

#ifndef __TinyZodiacs__HeroDTO__
#define __TinyZodiacs__HeroDTO__

#include <iostream>
#include "cocos2d.h"
#include "CharacterDTO.h"

USING_NS_CC;

class HeroDTO: public CharacterDTO
{
private:
protected:
public:
    HeroDTO();
    ~HeroDTO();

    CREATE_FUNC(HeroDTO);
};

#endif /* defined(__TinyZodiacs__HeroDTO__) */
