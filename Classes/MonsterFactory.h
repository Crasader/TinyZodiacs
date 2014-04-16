//
//  MonsterFactory.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/15/14.
//
//

#ifndef __TinyZodiacs__MonsterFactory__
#define __TinyZodiacs__MonsterFactory__

#include <iostream>
#include "cocos2d.h"
#include "Monster.h"
#include "CharacterFactory.h"

USING_NS_CC;

class MonsterFactory {
    
    
private:
    MonsterFactory();
protected:
public:
   virtual ~MonsterFactory();
   static MonsterFactory* getSharedFactory();
    
    Monster* createMonster(b2World* world);
 
};

#endif /* defined(__TinyZodiacs__MonsterFactory__) */
