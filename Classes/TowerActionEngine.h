//
//  TowerActionEngine.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/21/14.
//
//

#ifndef __TinyZodiacs__TowerActionEngine__
#define __TinyZodiacs__TowerActionEngine__

#include <iostream>
#include "ActionEngine.h"
#include "Tower.h"


class TowerActionEngine
{
private:
protected:
    CC_SYNTHESIZE(Tower*, tower, Tower);
    TowerActionEngine(Tower* tower);
    ~TowerActionEngine();
public:
    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();
    virtual void fallDown();
    virtual void attack();
    virtual void skill1();
    virtual void skill2();
    virtual void stopMoveAction();
};

#endif /* defined(__TinyZodiacs__TowerActionEngine__) */
