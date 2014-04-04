//
//  GameManager.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 1/8/14.
//
//

#include "GameManager.h"

USING_NS_CC;
static GameManager* sharedFactory = NULL;

GameManager::GameManager()
{
    
}

GameManager::~GameManager()
{
    
}

bool GameManager::loadResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monkey_spritesheet.plist", "monkey_spritesheet.png");

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map2_background_spritesheet.plist", "map2_background_spritesheet.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map2_background2_spritesheet.plist", "map2_background2_spritesheet.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map2_background3_spritesheet.plist", "map2_background3_spritesheet.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_1.plist", "map1_spritesheet_1.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_2.plist", "map1_spritesheet_2.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_3.plist", "map1_spritesheet_3.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_4.plist", "map1_spritesheet_4.png");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_1.plist", "map1_background_spritesheet_1.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_2.plist", "map1_background_spritesheet_2.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test_sheet.plist", "test_sheet.png");

    
    gbox2d::GB2ShapeCache *sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    sc->addShapesWithFile("body.plist");
    
    sc->addShapesWithFile("map_body.plist");
    sc->addShapesWithFile("map2_body.plist");

    sc->addShapesWithFile("character_body.plist");
    sc->addShapesWithFile("skill_body.plist");


    sc->addShapesWithFile("map1_body.plist");

    
    
    AnimationFactory::getSharedFactory()->loadXMLAnimation();
    MapFactory::getSharedFactory()->loadXMLMap();
    
    return false;
}

GameManager* GameManager::getSharedManager()
{
    if (!sharedFactory)
    {
        sharedFactory = new GameManager();
        //  this->sharedFactory->init();
    }
    return sharedFactory;
    
}
