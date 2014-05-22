//
//  ItemFactory.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#ifndef __TinyZodiacs__ItemFactory__
#define __TinyZodiacs__ItemFactory__
class ItemFactory;
#include <iostream>
#include "cocos2d.h"
#include "DataCollector.h"
#include "Constants.h"
#include "LayerIndexConstants.h"
#include "Item.h"
#include "ObjectFactory.h"

USING_NS_CC;
using namespace std;
class ItemFactory: public Observer
{
private:
    ItemFactory();
    GameHolder* holder;
    CCArray* listItem;
    vector<ItemStruct> listItemStructPrepareToCreate;
protected:

public:
    ~ItemFactory();
    
    static ItemFactory* getInstance();
    void update(float dt);
    
    void setHolder(GameHolder* holder);
    Item* createItem(const char* id, CCPoint position);
    void destroyItem(Item* item);
    
    void notifyToDestroy(GameObject* gameObject);
    void addItemPrepareToCreate(ItemStruct itemStruct);
};

#endif /* defined(__TinyZodiacs__ItemFactory__) */
