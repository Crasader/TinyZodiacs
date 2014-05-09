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
#include "ScheduleManager.h"
#include "ItemFactory.h"

USING_NS_CC;

class Item: public GameObject {
private:
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CCAction* lifeTimeAction;
protected:
public:
    Item();
    ~Item();
    
    virtual bool init();
    
    void destroy();
    void startSchedule();
    
    
    CREATE_FUNC(Item);
};

#endif /* defined(__TinyZodiacs__Item__) */
