//
//  CharacterActionEngine.h
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#ifndef __TinyZodiacs__CharacterActionEngine__
#define __TinyZodiacs__CharacterActionEngine__

#include <iostream>
#include "cocos2d.h"
#include "ActionEngine.h"
#include "Character.h"

USING_NS_CC;
class CharacterActionEngine: ActionEngine
{
private:
protected:
public:
    CC_SYNTHESIZE(Character*, character, Character);
    CharacterActionEngine(Character* character);
    ~CharacterActionEngine();
    
    virtual void moveLeft();
    virtual void moveRight();
    virtual void jump();
    virtual void fallDown();
    virtual void attack();
    virtual void skill1();
    virtual void skill2();
    virtual void stopMoveAction();
};
#endif /* defined(__TinyZodiacs__CharacterActionEngine__) */
