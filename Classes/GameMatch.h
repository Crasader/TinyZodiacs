//
//  GameMatch.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/22/14.
//
//

#ifndef __TinyZodiacs__GameMatch__
#define __TinyZodiacs__GameMatch__

class GameMatch;

#include <iostream>
#include "cocos2d.h"
#include "Map.h"
#include "GameWorld.h"
#include "Rule1.h"
#include "GameRule.h"
#include "ControllerManager.h"
#include "RuleManager.h"
#include "PhysicConstants.h"
#include "ScheduleManager.h"
#include "ControllerManager.h"

USING_NS_CC;

class GameMatch: public CCNode
{
private:
    int currentWave;
    int oldWave;
protected:
    CC_SYNTHESIZE(GameRule*, rule, Rule);
    CC_SYNTHESIZE(GameWorld*, gameWorld, GameWorld);
public:
    GameMatch();
    ~GameMatch();
    
    virtual bool init();
    virtual void update(float dt);
    
    void updateToCheckMatch();
    void start();
    void stop();
    void nextWave();
    bool checkWin();
    bool checkLose();
    bool checkNextWave();
    void prepareToEnterNewWave();
    void prepareToExitWave();
    void enterWave();
    void exitWave();
    
    CREATE_FUNC(GameMatch);
};

#endif /* defined(__TinyZodiacs__GameMatch__) */
