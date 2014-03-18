//
//  GameManager.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/8/14.
//
//

#ifndef __SampleCocosProject__GameManager__
#define __SampleCocosProject__GameManager__

#include <iostream>
#include "cocos2d.h"
#include "AnimationFactory.h"
#include "GB2ShapeCache-x.h"
#include "MapFactory.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    static bool loadResource();
    static GameManager* getSharedManager();
    
};

#endif /* defined(__SampleCocosProject__GameManager__) */
