//
//  Player.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__Player__
#define __TinyZodiacs__Player__

class Player;

#include <iostream>
#include "cocos2d.h"
#include "MainHero.h"
#include "ObjectFactory.h"
#include "Controller.h"
#include "Achievement.h"

USING_NS_CC;

class Player: public CCNode, public Controller
{
private:
    CC_SYNTHESIZE(Achievement*, achievement, Achievement);
    CC_SYNTHESIZE(MainHero*, hero, Hero);
protected:
public:
    Player();
    ~Player();
    
    virtual bool init();
    virtual void update(float dt);
    void attachWithHero(const char* heroID);
    void attachWithHero(Hero* hero);
    void reviveHero();
    virtual bool receiveCommand(CommandID commandID, void* data);
    
    CREATE_FUNC(Player);
};

#endif /* defined(__TinyZodiacs__Player__) */
