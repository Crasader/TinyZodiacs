//
//  Rule1.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/28/14.
//
//

#ifndef __TinyZodiacs__Rule1__
#define __TinyZodiacs__Rule1__

#include <iostream>
#include "GameRule.h"
#include "RuleManager.h"

class Rule1: public GameRule
{
private:
protected:
public:
    Rule1();
    ~Rule1();
    
    virtual bool checkWin();
    virtual bool checkLose();
    virtual bool checkNextWave();
    virtual void update(float dt);
    
};

#endif /* defined(__TinyZodiacs__Rule1__) */
