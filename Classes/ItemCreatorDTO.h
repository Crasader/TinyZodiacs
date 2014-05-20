//
//  ItemCreator.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#ifndef __TinyZodiacs__ItemCreatorDTO__
#define __TinyZodiacs__ItemCreatorDTO__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;
using namespace std;

class ItemCreatorDTO: public CCObject
{
private:
protected:
public:
    ItemCreatorDTO();
    ~ItemCreatorDTO();
    
    virtual bool init();
    
    int max;
    float delayMin;
    float delayMax;
    float beginPositionX;
    float beginPositionY;
    float endPositionX;
    float endPositionY;
    
    vector<ItemStruct> listItem;
    
    
    CREATE_FUNC(ItemCreatorDTO);
};

#endif /* defined(__TinyZodiacs__ItemCreatorDTO__) */
