//
//  GoldItem.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#ifndef __TinyZodiacs__GoldItem__
#define __TinyZodiacs__GoldItem__

#include <iostream>
#include "cocos2d.h"
#include "Item.h"
#include "Constants.h"

USING_NS_CC;
using namespace std;
class GoldItem: public Item
{
private:
protected:
public:
    GoldItem();
    virtual ~GoldItem();
    
    virtual bool init();
    
    virtual void onCreate();
    virtual void destroy();
    virtual void startSchedule();
    
    virtual void prepareToAppear();
    virtual void appear();
    virtual void prepareToDisappearInTimeOut();
    virtual void prepareToDisappearInContact(GameObject* contactGameObject);
    virtual void prepareToDisappearInOpen();
    virtual void disappear();
    
    virtual void contact(GameObject* contactGameObject);
    virtual void open(GameObject* openGameObject);
    
    CREATE_FUNC(GoldItem);
    
};

#endif /* defined(__TinyZodiacs__GoldItem__) */
