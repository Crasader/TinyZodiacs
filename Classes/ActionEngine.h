//
//  ActionEngine.h
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#ifndef __TinyZodiacs__ActionEngine__
#define __TinyZodiacs__ActionEngine__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class ActionEngine
{
private:
public:
    virtual void moveLeft()=0;
    virtual void moveRight()=0;
    virtual void jump()=0;
    virtual void fallDown()=0;
    virtual void attack()=0;
    virtual void skill1()=0;
    virtual void skill2()=0;
    virtual void stopMoveAction()=0;

protected:
};
#endif /* defined(__TinyZodiacs__ActionEngine__) */
