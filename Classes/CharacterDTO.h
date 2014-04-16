//
//  CharacterDTO.h
//  TinyZodiacs
//
//  Created by Nhut on 3/24/14.
//
//

#ifndef __TinyZodiacs__CharacterDTO__
#define __TinyZodiacs__CharacterDTO__

#include <iostream>
#include "Box2D/Box2D.h"
#include "CharacterData.h"
#include "cocos2d.h"

class CharacterDTO
{
private:
protected:
public:
    CharacterDTO();
    ~CharacterDTO();
    
    string body;
    string animation;
    CharacterData data;
};

#endif /* defined(__TinyZodiacs__CharacterDTO__) */
