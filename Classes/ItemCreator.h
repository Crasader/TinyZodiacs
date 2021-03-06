//
//  ItemCreator.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#ifndef __TinyZodiacs__ItemCreator__
#define __TinyZodiacs__ItemCreator__

class ItemCreator;

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "ItemFactory.h"
#include "Observer.h"
#include "Util.h"

USING_NS_CC;
using namespace std;

class ItemCreator: public CCObject, public Observer
{
private:
    CCAction* delayAction;
    bool isStopped;
    CC_SYNTHESIZE(CCArray*, listItem, ListItem);
protected:
    CC_SYNTHESIZE(CCPoint, beginPosition, BeginPosition);
    CC_SYNTHESIZE(CCPoint, endPosition, EndPosition);
    CC_SYNTHESIZE(int, max, Max);
    CC_SYNTHESIZE(float, delayMin, DelayMin);
    CC_SYNTHESIZE(float, delayMax, DelayMax);
    CC_SYNTHESIZE(vector<ItemStruct>, listItemStruct, ListItemStructDelayMax);

public:
    ItemCreator();
    ~ItemCreator();
    
    virtual bool init();
    
    void start();
    void stop();
    void createItem();
    void notifyToDestroy(GameObject* object);
    
    CREATE_FUNC(ItemCreator);
};
#endif /* defined(__TinyZodiacs__ItemCreator__) */
