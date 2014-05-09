//
//  ItemDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__ItemDTO__
#define __TinyZodiacs__ItemDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class ItemDTO: public CCObject
{
private:
protected:
public:
    ItemDTO();
    ~ItemDTO();
    
    virtual bool init();
    
    string id;
    string imageName;
    string bodyName;
    float positionX;
    float positionY;
    float lifeTime;
    
    CREATE_FUNC(ItemDTO);
};

#endif /* defined(__TinyZodiacs__ItemDTO__) */
