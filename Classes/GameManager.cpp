//
//  GameManager.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 1/8/14.
//
//

#include "GameManager.h"
#include "ItemLoader.h"

USING_NS_CC;
static GameManager* instance = NULL;

GameManager::GameManager()
{
    
}

GameManager::~GameManager()
{
    
}

GameManager* GameManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new GameManager();
    }
    return instance;
}

bool GameManager::loadResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monkey_spritesheet.plist", "monkey_spritesheet.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cat_spritesheet.plist", "cat_spritesheet.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_1.plist", "map1_spritesheet_1.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_2.plist", "map1_spritesheet_2.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_3.plist", "map1_spritesheet_3.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_4.plist", "map1_spritesheet_4.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_1.plist", "map1_background_spritesheet_1.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_2.plist", "map1_background_spritesheet_2.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test_sheet.plist", "test_sheet.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower_1_default.plist", "tower_1_default.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower_2_default.plist", "tower_2_default.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tower_orb_default.plist", "tower_orb_default.png");
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("smoke_spritesheet.plist", "smoke_spritesheet.png");
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("item_spritesheet.plist", "item_spritesheet.png");
    
    gbox2d::GB2ShapeCache *sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    sc->addShapesWithFile("character_body.plist");
    sc->addShapesWithFile("cat_body.plist");
    sc->addShapesWithFile("skill_body.plist");
    sc->addShapesWithFile("map1_body.plist");
    sc->addShapesWithFile("monster_sensor.plist");
    sc->addShapesWithFile("item_body.plist");
    return false;
}

bool GameManager::loadData()
{
    AnimationLoader::loadData();
    MapLoader::loadData();
    HeroLoader::loadData();
    MonsterLoader::loadData();
    ItemLoader::loadData();
    
    
    return true;
}


