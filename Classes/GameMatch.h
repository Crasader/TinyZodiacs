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
#include "Player.h"
#include "MainMenuScene.h"

USING_NS_CC;

class GameMatch: public CCNode, public Controller
{
private:
    bool isWaveEntered;
    bool isStopped;
    int currentWave;
    int oldWave;
protected:
    CC_SYNTHESIZE(Player*, player, Player);
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
    void displayMonsterCount();
    void initHeroPosition();
    void destroy();
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    
    CREATE_FUNC(GameMatch);
};

#endif /* defined(__TinyZodiacs__GameMatch__) */
