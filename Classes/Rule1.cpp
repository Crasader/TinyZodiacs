//
//  Rule1.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/28/14.
//
//

#include "Rule1.h"

Rule1::Rule1()
{
    
}

Rule1::~Rule1()
{
    
}

void Rule1::update(float dt)
{

}

bool Rule1::checkWin()
{
    if(RuleManager::getInstance()->getRuleEvent(RULE_EVENT_COMPLETE_ALL_WAVE))
    {
        return true;
    }
    
    return false;

}

bool Rule1::checkLose()
{
    if(RuleManager::getInstance()->getRuleEvent(RULE_EVENT_MAIN_CRYSTAL_DESTROYED))
    {
        return true;
    }
    return false;
}

bool Rule1::checkNextWave()
{
    if(RuleManager::getInstance()->getRuleEvent(RULE_EVENT_COMPLETE_KILL_ALL_MONSTER_IN_WAVE))
    {
        return true;
    }
    
    return false;
}
