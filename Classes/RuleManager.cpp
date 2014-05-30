//
//  RuleManager.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/28/14.
//
//

#include "RuleManager.h"

static RuleManager* instance = NULL;

RuleManager::RuleManager()
{
//    this->listRuleEvent = CCDictionary::create();
//    this->listRuleEvent->retain();
}

RuleManager::~RuleManager()
{
    
}

RuleManager* RuleManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new RuleManager();
    }
    return instance;
}

void RuleManager::addRuleEvent(RuleEventID ruleEventID, bool result)
{
    map<RuleEventID, bool>::iterator it = this->listRuleEvent.find(ruleEventID);
    
    if(it != listRuleEvent.end())
    {
        this->listRuleEvent.erase(it);
    }

    this->listRuleEvent.insert(make_pair(ruleEventID, result));
}

void RuleManager::clean()
{
    this->listRuleEvent.clear();
}

bool RuleManager::getRuleEvent(RuleEventID ruleEventID)
{
    map<RuleEventID, bool>::iterator it = this->listRuleEvent.find(ruleEventID);
    
    if(it != listRuleEvent.end())
    {
        if(it->second == true)
        {
            return true;
        }
        return false;
    }
    return false;
}