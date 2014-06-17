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
    
    
    //
    loadSpritesheet("thumbnail_spritesheet.png","thumbnail_spritesheet.plist", kCCTexture2DPixelFormat_RGBA8888);
    loadSpritesheet("ui_spritesheet_3.png","ui_spritesheet_3.plist", kCCTexture2DPixelFormat_RGBA8888);
    loadSpritesheet("ui_spritesheet_2.png","ui_spritesheet_2.plist", kCCTexture2DPixelFormat_RGBA8888);
    loadSpritesheet("ui_spritesheet_1.png","ui_spritesheet_1.plist", kCCTexture2DPixelFormat_RGBA8888);
    loadSpritesheet("mainmenu_spritesheet.png","mainmenu_spritesheet.plist", kCCTexture2DPixelFormat_RGBA8888);
    
    
    loadSpritesheet("test_sheet.png","test_sheet.plist", kCCTexture2DPixelFormat_RGBA8888);
    
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    
    
    gbox2d::GB2ShapeCache *sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addShapesWithFile("character_body.plist");
    sc->addShapesWithFile("skill_body.plist");
    sc->addShapesWithFile("map1_body.plist");
    sc->addShapesWithFile("monster_sensor.plist");
    sc->addShapesWithFile("item_body.plist");
    sc->addShapesWithFile("tower_sensor.plist");
    
    return false;
}


bool GameManager::loadSpritesheet(const char* imageFileName, const char* plistFilename, CCTexture2DPixelFormat texturePixelFormat)
{
    CCTexture2DPixelFormat old = CCTexture2D::defaultAlphaPixelFormat();
    
    if(old != texturePixelFormat)
    {
        CCTexture2D::setDefaultAlphaPixelFormat(texturePixelFormat);
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename, imageFileName);
    
    CCTexture2D::setDefaultAlphaPixelFormat(old);
    return true;
}


bool GameManager::loadData()
{
    //AnimationLoader::loadData();
    TowerLoader::loadData();
    MapLoader::loadData();
    HeroLoader::loadData();
    MonsterLoader::loadData();
    ItemLoader::loadData();
    
    return true;
}

void GameManager::initManager()
{
    instance->addChild(ScheduleManager::getInstance());
    instance->addChild(GameObjectManager::getInstance());
    instance->addChild(EffectManager::getInstance());
}


