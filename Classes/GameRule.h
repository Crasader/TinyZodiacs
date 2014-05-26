//
//  GameRule.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/24/14.
//
//

#ifndef __TinyZodiacs__GameRule__
#define __TinyZodiacs__GameRule__

#include <iostream>

class GameRule
{
private:
protected:
public:
    virtual bool checkWin() = 0;
    virtual bool checkLose() = 0;
};

#endif /* defined(__TinyZodiacs__GameRule__) */
