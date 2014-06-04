//
//  MainHero.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#ifndef __TinyZodiacs__MainHero__
#define __TinyZodiacs__MainHero__

class MainHero;

#include <iostream>
#include "cocos2d.h"
#include "Hero.h"
#include "ControllerManager.h"
#include "EffectManager.h"

USING_NS_CC;

class MainHero: public Hero
{
private:
    CCAction* reviveAction;
protected:
public:
 
    bool isDead;
    MainHero();
    virtual ~MainHero();
    
    virtual bool init();
    virtual void update(float dt);
    virtual void destroy();
    
    virtual void die();
    void revive();
    
    CREATE_FUNC(MainHero);
};

#endif /* defined(__TinyZodiacs__MainHero__) */
