//
//  ItemFactory.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__ItemFactory__
#define __TinyZodiacs__ItemFactory__

#include <iostream>
#include "cocos2d.h"
#include "DataCollector.h"
#include "Constants.h"
#include "LayerIndexConstants.h"
#include "Item.h"
#include "ObjectFactory.h"

USING_NS_CC;
class Item;

class ItemFactory
{
private:
    ItemFactory();
    GameHolder* holder;
    CCArray* listItem;
protected:

public:
    ~ItemFactory();
    
    static ItemFactory* getInstance();
    void update(float dt);
    
    void setHolder(GameHolder* holder);
    void createItem(const char* id, CCPoint position);
    void destroyItem(Item* item);
};

#endif /* defined(__TinyZodiacs__ItemFactory__) */
