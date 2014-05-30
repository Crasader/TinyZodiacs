//
//  RuleManager.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/28/14.
//
//

#ifndef __TinyZodiacs__RuleManager__
#define __TinyZodiacs__RuleManager__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
using namespace std;

USING_NS_CC;

class RuleManager
{
private:
    map<RuleEventID, bool> listRuleEvent;
protected:
public:
    RuleManager();
    ~RuleManager();
    
    static RuleManager* getInstance();
    
    void addRuleEvent(RuleEventID ruleEventID, bool result);
    bool getRuleEvent(RuleEventID ruleEventID);
    void clean();
    
};

#endif /* defined(__TinyZodiacs__RuleManager__) */
