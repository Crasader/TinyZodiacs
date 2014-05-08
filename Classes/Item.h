//
//  Item.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__Item__
#define __TinyZodiacs__Item__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class Item: public GameObject {
private:
protected:
public:
    Item();
    ~Item();
    
    virtual bool init();
    
    CREATE_FUNC(Item);
};

#endif /* defined(__TinyZodiacs__Item__) */
