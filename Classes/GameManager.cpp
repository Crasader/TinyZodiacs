//
//  GameManager.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 1/8/14.
//
//

#include "GameManager.h"
#include "AnimationFactory.h"
#include "GB2ShapeCache-x.h"
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

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background_sheet_1.plist", "background_sheet_1.png");
   
   
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map_spritesheet.plist", "map_spritesheet.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monkey_spritesheet.plist", "monkey_spritesheet.png");
    
    
    gbox2d::GB2ShapeCache *sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    sc->addShapesWithFile("body.plist");

    sc->addShapesWithFile("map_body.plist");
    

    
    AnimationFactory::getSharedFactory()->loadXMLAnimation();
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
