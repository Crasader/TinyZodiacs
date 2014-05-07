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
#include "MonsterCreatorDTO.h"
#include "MonsterCreator.h"
#include "MonsterDTO.h"

#define MONSTER_CREATION_DELAY 1;

USING_NS_CC;

class MonsterFactory: public CCObject {
    
private:
    CC_SYNTHESIZE(Group, group, Group);
    CC_SYNTHESIZE(CCNode*, holder, Holder);
    CC_SYNTHESIZE(CCArray*, listMonster, ListMonster);
    CC_SYNTHESIZE(b2World*, world, World);
    CC_SYNTHESIZE(CCArray*, listMonsterCreator, ListMonsterCreator);
protected:
public:
    MonsterFactory();
    virtual ~MonsterFactory();

    virtual bool init();
    virtual void update(float dt);
    
    Monster* createMonster(MonsterDTO* monsterDTO, CCPoint position, int laneID, b2World* world);
//    void createMonsters(CharacterDTO* monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster);
    void createMonsterList(CCArray* listMonsterDTO, CCPoint position, int laneID, int quantity, float timeDelayPerMonster);
    void createMonsterFromSchedule(CCNode* sender, void* data);
    void finishCreateMonsterFromSchedule(CCNode* sender, void* data);
    void createMonsterListFromSchedule(CCNode* sender, void* data);
    void finishCreateMonsterListFromSchedule(CCNode* sender, void* data);
    void addNewMonster(Monster* monster);
    void removeMonster(Monster* monster);
    void registerMonsterCreator(MonsterCreatorDTO* monsterCreatorDTO, b2World* world);
    void stopCreateMonster();
    void startCreateMonster();

 
    
    CREATE_FUNC(MonsterFactory);
    
};

#endif /* defined(__TinyZodiacs__MonsterFactory__) */
