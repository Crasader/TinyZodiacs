//
//  Achievement.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/16/14.
//
//

#ifndef __TinyZodiacs__Achievement__
#define __TinyZodiacs__Achievement__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Achievement
{
private:
    CC_SYNTHESIZE(int, gold, Gold);
    CC_SYNTHESIZE(int, time, Time);
    CC_SYNTHESIZE(int, score, Score);
protected:
public:
    void addScore(int score);
    void addGold(int gold);
    
    Achievement();
    ~Achievement();
    
};

#endif /* defined(__TinyZodiacs__Achievement__) */
