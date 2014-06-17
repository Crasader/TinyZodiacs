//
//  GameManager.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/8/14.
//
//

#ifndef __SampleCocosProject__GameManager__
#define __SampleCocosProject__GameManager__

class GameManager;

#include <iostream>
#include "cocos2d.h"
#include "AnimationLoader.h"
#include "GB2ShapeCache-x.h"
#include "MapFactory.h"
#include "MapLoader.h"
#include "HeroLoader.h"
#include "MonsterLoader.h"
#include "XMLMonsterParser.h"
#include "TowerLoader.h"
#include "EffectManager.h"
#include "GameObjectManager.h"
#include "ScheduleManager.h"

USING_NS_CC;

class GameManager: public CCNode
{
private:
    CC_SYNTHESIZE(GameHolder, gameplayHolder, GameplayHolder);
protected:
public:
    int totalResource = 0;
    int currentIndexResourceloaded = 0;
    GameManager();
    ~GameManager();
    
    bool loadResource();
    bool loadSpritesheet(const char* imageFileName, const char* plistFilename, CCTexture2DPixelFormat texturePixelFormat = kCCTexture2DPixelFormat_RGBA4444);
    bool loadData();
    void initManager();
    
    
    static GameManager* getInstance();
    
};

#endif /* defined(__SampleCocosProject__GameManager__) */
