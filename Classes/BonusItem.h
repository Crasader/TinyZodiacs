//
//  BonusItem.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/19/14.
//
//

#ifndef __TinyZodiacs__BonusItem__
#define __TinyZodiacs__BonusItem__

class BodyItem;

#include <iostream>
#include "cocos2d.h"
#include "Item.h"
#include "Constants.h"
#include "EffectData.h"
#include "EffectManager.h"
#include "TextShowEffect.h"

USING_NS_CC;
using namespace std;
class BonusItem: public Item
{
private:
    CC_SYNTHESIZE(vector<EffectData>, listEffectData, ListEffectData);
    CC_SYNTHESIZE(string, titleNotification, TitleNotification);
protected:
public:
    BonusItem();
    virtual ~BonusItem();
    
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
    
    CREATE_FUNC(BonusItem);
    
};

#endif /* defined(__TinyZodiacs__BonusItem__) */
