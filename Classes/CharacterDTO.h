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

USING_NS_CC;

class CharacterDTO: public CCObject
{
private:
protected:
public:
    CharacterDTO();
    ~CharacterDTO();
    
    virtual bool init();
    
    string body;
    string animation;
    CharacterData data;
    
    int getRefenceCount();
    
    CREATE_FUNC(CharacterDTO);
};

#endif /* defined(__TinyZodiacs__CharacterDTO__) */
