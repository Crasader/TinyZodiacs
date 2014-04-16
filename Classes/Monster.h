//
//  Monster.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__Monster__
#define __Headball__Monster__

#include <iostream>
#include "cocos2d.h"
#include "Character.h"

USING_NS_CC;

class Monster: public Character
{
private:
protected:
public:
    Monster();
    ~Monster();
    
    virtual bool init();
    
    CREATE_FUNC(Monster);
    
};

#endif /* defined(__Headball__Monster__) */
