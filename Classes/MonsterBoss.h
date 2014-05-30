//
//  MonsterBoss.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/30/14.
//
//

#ifndef __TinyZodiacs__MonsterBoss__
#define __TinyZodiacs__MonsterBoss__

#include <iostream>
#include "cocos2d.h"
#include "Monster.h"
#include "RuleManager.h"

USING_NS_CC;

class MonsterBoss: public Monster
{
private:
protected:
public:
    MonsterBoss();
    ~MonsterBoss();
    
    virtual void destroy();
    
    CREATE_FUNC(MonsterBoss);
};

#endif /* defined(__TinyZodiacs__MonsterBoss__) */
