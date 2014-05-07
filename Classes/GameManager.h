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
#include "AnimationLoader.h"
#include "GB2ShapeCache-x.h"
#include "MapFactory.h"
#include "MapLoader.h"
#include "HeroLoader.h"
#include "MonsterLoader.h"
#include "XMLMonsterParser.h"


class GameManager
{
public:
    GameManager();
    ~GameManager();
    bool loadResource();
    bool loadData();
    
    static GameManager* getInstance();
    
};

#endif /* defined(__SampleCocosProject__GameManager__) */
