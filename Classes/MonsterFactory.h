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

#define MONSTER_CREATION_DELAY 1;

USING_NS_CC;

class MonsterFactory {
    
    
private:
    MonsterFactory();
    
    
protected:
public:
    CC_SYNTHESIZE(CCNode*, holder, Holder)
    
   virtual ~MonsterFactory();
    CCArray* listMonster;

   static MonsterFactory* getSharedFactory();
    
    
    Monster* createMonster(CharacterDTO characterDTO, CCPoint position, b2World* world);
    void createMonsters(CharacterDTO monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster, b2World* world);
    
    void createMonsterFromSchedule(CCNode* sender, void* data);
    void finishCreateMonsterFromSchedule(CCNode* sender, void* data);
    
    void addNewMonster(Monster* monster);
    void removeMonster(Monster* monster);
    
    void update(float dt);
    
};

#endif /* defined(__TinyZodiacs__MonsterFactory__) */
