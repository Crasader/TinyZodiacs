//
//  TestScene.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "TestScene.h"
#include "Cocos2d.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "GameBackgroundLayer.h"
#include "GameObjectLayer.h"
#include "LayerIndexConstants.h"
#include "GameplayLayer.h"
#include "ControllerManager.h"
#include "SoundManager.h"
USING_NS_CC;

bool TestScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    if(GameManager::getInstance()->getParent() == NULL)
    {
        this->addChild(GameManager::getInstance());
        GameManager::getInstance()->pauseSchedulerAndActions();
    }
    return true;
}

TestScene::~TestScene()
{
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    for(int i=0; i<DataCollector::getInstance()->getMatchData()->resourcePackList.size(); i++)
    {
        ResourceLoader::unloadResourcePack(DataCollector::getInstance()->getMatchData()->resourcePackList[i]);
    }
    
    ResourceLoader::unloadResourcePack(this->resourcePack);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    this->resourcePack->release();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCDirector::sharedDirector()->purgeCachedData();
    
    ControllerManager::getInstance()->clean();
    RuleManager::getInstance()->clean();
    SoundManager::playMenuMusic();
    
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

CCScene* TestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestScene *layer = TestScene::create();
    // add layer as a child to scene
    scene->addChild(layer, 0, 1);
    
    // return the scene
    return scene;
}

void TestScene::initScene()
{
    GameplayLayer* menuLayer = GameplayLayer::create();
    this->addChild(menuLayer, GAME_MENU_LAYER, 4);
    //
    GameObjectLayer* objectLayer = GameObjectLayer::create();
    this->addChild(objectLayer, GAME_OBJECT_LAYER, 3);
}

void TestScene::loadResource()
{
    this->resourcePack = XMLResourcePackParser::getResourcePackInFile("gameplay_resource", "resource_list.xml");
    this->resourcePack->retain();
    ResourceLoader::loadResourcePack(resourcePack);
}
