//
//  MonsterCreator.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/30/14.
//
//

#ifndef __TinyZodiacs__MonsterCreator__
#define __TinyZodiacs__MonsterCreator__

#include <iostream>
#include "cocos2d.h"
#include "MonsterFactory.h"
#include "ScheduleManager.h"

USING_NS_CC;

class MonsterFactory;
class MonsterCreator: public CCObject {
    
private:
    CCAction* actionCreateMonster;
    CC_SYNTHESIZE(MonsterFactory*, monsterFactory, MonsterFactory);
    CC_SYNTHESIZE(float, delay, Delay);
    CC_SYNTHESIZE(float, delayPerUnit, DelayPerUnit);
    CC_SYNTHESIZE(std::vector<std::string>, listMonsterID, ListMonsterID);
    CC_SYNTHESIZE(CCPoint, position, Position);
    CC_SYNTHESIZE(int, laneID, LaneID);
protected:
public:
    MonsterCreator();
    virtual ~MonsterCreator();
    
    virtual bool init();
    
    void createMonster();
    void start();
    void stop();
    
    CREATE_FUNC(MonsterCreator);
};

#endif /* defined(__TinyZodiacs__MonsterCreator__) */
