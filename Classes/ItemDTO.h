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
#include "Constants.h"

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
    string type;
    string imageName;
    string bodyName;
    string animation;
    float positionX;
    float positionY;
    float lifeTime;
    int goldValue;
    
    vector<ItemStruct> listSubItemStruct;
    vector<string> listAffectID;
    
    
    CREATE_FUNC(ItemDTO);
};

#endif /* defined(__TinyZodiacs__ItemDTO__) */
