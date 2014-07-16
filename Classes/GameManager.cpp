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

    
    
    gbox2d::GB2ShapeCache *sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addShapesWithFile("character_body.plist");
    sc->addShapesWithFile("skill_body.plist");
    sc->addShapesWithFile("map1_body.plist");
    sc->addShapesWithFile("monster_sensor.plist");
    sc->addShapesWithFile("item_body.plist");
    sc->addShapesWithFile("tower_sensor.plist");
    sc->addShapesWithFile("tower_body.plist");
    
    return false;
}


bool GameManager::loadSpritesheet(const char* imageFileName, const char* plistFilename, CCTexture2DPixelFormat texturePixelFormat)
{
    CCLOG("load spritesheet: %s", imageFileName);
    
    CCTexture2DPixelFormat old = CCTexture2D::defaultAlphaPixelFormat();
    CCTexture2D::setDefaultAlphaPixelFormat(texturePixelFormat);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename, imageFileName);
    
    CCTexture2D::setDefaultAlphaPixelFormat(old);
    return true;
}

bool GameManager::loadSpritesheet(const char* imageFileName, const char* plistFilename)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename, imageFileName);
    return true;
}


bool GameManager::loadData()
{
    //AnimationLoader::loadData();
    ResourceLoader::loadData();
    TowerLoader::loadData();
    MapLoader::loadData();
    HeroLoader::loadData();
   // MonsterLoader::loadData();
    ItemLoader::loadData();
    
  
    
    return true;
}

void GameManager::initManager()
{
//    if(ScheduleManager::getInstance()->)
//    {
//        
//    }
    instance->addChild(ScheduleManager::getInstance());
    instance->addChild(GameObjectManager::getInstance());
    instance->addChild(EffectManager::getInstance());
}


