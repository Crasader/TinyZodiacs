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

class MonsterFactory: public CCObject {
    
    
private:
protected:
public:
    
    CC_SYNTHESIZE(CCNode*, holder, Holder);
    CC_SYNTHESIZE(CCArray*, listMonster, ListMonster);
    
    MonsterFactory();
    virtual ~MonsterFactory();

    virtual bool init();
    void update(float dt);
    
    Monster* createMonster(CharacterDTO characterDTO, CCPoint position, b2World* world);
    void createMonsters(CharacterDTO monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster, b2World* world);
    void createMonsterFromSchedule(CCNode* sender, void* data);
    void finishCreateMonsterFromSchedule(CCNode* sender, void* data);
    void addNewMonster(Monster* monster);
    void removeMonster(Monster* monster);
    
 
    
    CREATE_FUNC(MonsterFactory);
    
};

#endif /* defined(__TinyZodiacs__MonsterFactory__) */
