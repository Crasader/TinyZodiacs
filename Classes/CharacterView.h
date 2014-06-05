//
//  HeroInfoView.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__CharacterView__
#define __TinyZodiacs__CharacterView__

#include <iostream>
#include "cocos2d.h"
#include "GameObjectView.h"
#include "Hero.h"

USING_NS_CC;

class CharacterView: public GameObjectView
{
private:
    HealthBar* healthBar;
    CCLabelTTF* textNameLabel;
    float holderHeight;
protected:
public:
    CharacterView();
    ~CharacterView();

    virtual bool init();
    virtual void update(float dt);
    
    virtual void attach(GameObject* gameObject);
    
    virtual void setHealthBar(HealthBar* healthBar);
    virtual void setTextNameLabel(CCLabelTTF* textNameLabel);
    virtual void notifyChange();
    
    CREATE_FUNC(CharacterView);
};

#endif /* defined(__TinyZodiacs__CharacterView__) */
