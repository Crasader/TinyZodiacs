//
//  Wave.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/21/14.
//
//

#ifndef __TinyZodiacs__Wave__
#define __TinyZodiacs__Wave__

class Wave;

#include <iostream>
#include "cocos2d.h"
#include "MonsterFactory.h"
#include "Constants.h"
#include "MonsterFactory.h"
#include "ItemCreator.h"

USING_NS_CC;

class Wave: public CCObject
{
private:
protected:
    CC_SYNTHESIZE(MonsterFactory*, monsterFactory, MonsterFactory);
    CC_SYNTHESIZE(CCArray*, listMonsterFactory, ListMonsterFactory);
    CC_SYNTHESIZE(CCArray*, listItemCreator, ListItemCreator);

public:
    Wave();
    ~Wave();
    
    void setHolder(GameHolder holder);
    virtual bool init();
    
    void addMonsterFactory(MonsterFactory* monsterFactory);
    void addItemCreator(ItemCreator* itemCreator);
    
    void startCreateMonster();
    void startCreateItem();
    void stopCreateMonster();
    void stopCreateItem();
    
    void start();
    void stop();
    
    int getMonsterCount();
    
    CREATE_FUNC(Wave);
};

#endif /* defined(__TinyZodiacs__Wave__) */
