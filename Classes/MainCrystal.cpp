//
//  MainCrystal.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/29/14.
//
//

#include "MainCrystal.h"

MainCrystal::MainCrystal()
{
    
}

MainCrystal::~MainCrystal()
{
    
}

void MainCrystal::destroy()
{
    Tower::destroy();
    
    RuleManager::getInstance()->addRuleEvent(RULE_EVENT_MAIN_CRYSTAL_DESTROYED, true);
}

void MainCrystal::die()
{
    Tower::die();
}