//
//  MonsterView.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/15/14.
//
//

#ifndef __TinyZodiacs__MonsterView__
#define __TinyZodiacs__MonsterView__

#include <iostream>
#include "cocos2d.h"
#include "GameObjectView.h"
#include "Hero.h"

class MonsterView: public GameObjectView
{
private:
    HealthBar* healthBar;
    CCLabelTTF* textNameLabel;
    
protected:
public:
    MonsterView();
    ~MonsterView();
    
    virtual bool init();
    virtual void update(float dt);
    
    virtual void attach(GameObject* gameObject);
    
    virtual void setHealthBar(HealthBar* healthBar);
    virtual void setTextNameLabel(CCLabelTTF* textNameLabel);
    
    CREATE_FUNC(MonsterView);
};

#endif /* defined(__TinyZodiacs__MonsterView__) */
