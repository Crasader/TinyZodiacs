//
//  MonsterBoss.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/30/14.
//
//

#include "MonsterBoss.h"

MonsterBoss::MonsterBoss()
{
    
}

MonsterBoss::~MonsterBoss()
{
    
}

void MonsterBoss::destroy()
{
    Monster::destroy();
    
    RuleManager::getInstance()->addRuleEvent(RULE_EVENT_BOSS_HAVE_BEEN_KILLED, true);
}