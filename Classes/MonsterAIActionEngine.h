//
//  MonsterAIActionEngine.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/21/14.
//
//

#ifndef __TinyZodiacs__MonsterAIActionEngine__
#define __TinyZodiacs__MonsterAIActionEngine__

#include <iostream>
#include "cocos2d.h"
#include "ActionEngine.h"


class MonsterAIActionEngine: public ActionEngine
{
private:
protected:
public:
    MonsterAIActionEngine();
    ~MonsterAIActionEngine();
    
    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();
    virtual void fallDown();
    virtual void attack();
    virtual void skill1();
    virtual void skill2();
    virtual void stopMoveAction();
};


#endif /* defined(__TinyZodiacs__MonsterAIActionEngine__) */
