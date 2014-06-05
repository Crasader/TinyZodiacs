//
//  MainCrystal.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/29/14.
//
//

#ifndef __TinyZodiacs__MainCrystal__
#define __TinyZodiacs__MainCrystal__

#include <iostream>
#include "cocos2d.h"
#include "Tower.h"
#include "RuleManager.h"
#include "CharacterDieState.h"

USING_NS_CC;

class MainCrystal: public Tower
{
private:
protected:
public:
    MainCrystal();
    ~MainCrystal();
    
    virtual void destroy();
    virtual void die();
    
    CREATE_FUNC(MainCrystal);
};


#endif /* defined(__TinyZodiacs__MainCrystal__) */
