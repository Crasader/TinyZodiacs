//
//  LoadingScene.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/11/14.
//
//

#include "LoadingScene.h"

bool LoadingScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    resourceCount = 0;
    currResourceCount = 0;
    initScene();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    return true;
}


LoadingScene::~LoadingScene()
{
    
}

CCScene* LoadingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LoadingScene *layer = LoadingScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);
    
    // return the scene
    return scene;
}


void LoadingScene::initScene()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
        CCSprite* background = CCSprite::createWithSpriteFrameName("LOADING.jpg");
        background->setAnchorPoint(ccp(0.5,0.5));
        background->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(background);
    //    HeroSelectLayer* layer = HeroSelectLayer::create();
    //    this->addChild(layer);
    
   
    
    this->runAction(CCSequence::create(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(LoadingScene::loadResource)), NULL));
   

}

void LoadingScene::loadResource()
{
    GameManager::getInstance()->loadSpritesheet("map1_spritesheet_4.png","map1_spritesheet_4.plist");
    GameManager::getInstance()->loadSpritesheet("map1_spritesheet_3.png","map1_spritesheet_3.plist");
    GameManager::getInstance()->loadSpritesheet("map1_spritesheet_2.png","map1_spritesheet_2.plist");
    GameManager::getInstance()->loadSpritesheet("map1_spritesheet_1.png","map1_spritesheet_1.plist");
    
    GameManager::getInstance()->loadSpritesheet("map1_background_spritesheet_3.png","map1_background_spritesheet_3.plist");
    GameManager::getInstance()->loadSpritesheet("map1_background_spritesheet_2.png","map1_background_spritesheet_2.plist");
    GameManager::getInstance()->loadSpritesheet("map1_background_spritesheet_1.png","map1_background_spritesheet_1.plist");
    
    
    GameManager::getInstance()->loadSpritesheet("onion_invert_spritesheet.png","onion_invert_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("tower_spritesheet.png","tower_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("pig_animation.png","pig_animation.plist");
    GameManager::getInstance()->loadSpritesheet("other_effect_spritesheet.png","other_effect_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("onion_spritesheet.png","onion_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("monkey_spritesheet.png","monkey_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("magic_mass_bomb_spritesheet_2.png","magic_mass_bomb_spritesheet_2.plist");
    GameManager::getInstance()->loadSpritesheet("magic_mass_bomb_spritesheet_1.png","magic_mass_bomb_spritesheet_1.plist");
    GameManager::getInstance()->loadSpritesheet("magic_lightning_arrow_spritesheet.png","magic_lightning_arrow_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("magic_fire_pillar_spritesheet_2.png","magic_fire_pillar_spritesheet_2.plist");
    GameManager::getInstance()->loadSpritesheet("magic_fire_pillar_spritesheet_1.png","magic_fire_pillar_spritesheet_1.plist");
//     GameManager::getInstance()->loadSpritesheet("magic_fire_ball_spritesheet.png","magic_fire_ball_spritesheet.plist");
    GameManager::getInstance()-> loadSpritesheet("magic_energy_ball_spritesheet.png","magic_energy_ball_spritesheet.plist");
//     GameManager::getInstance()->loadSpritesheet("magic_bomb_start_spritesheet.png","magic_bomb_start_spritesheet.plist");
    GameManager::getInstance()-> loadSpritesheet("item_spritesheet.png","item_spritesheet.plist");
    GameManager::getInstance()->loadSpritesheet("cat_spritesheet.png","cat_spritesheet.plist");
    GameManager::getInstance()-> loadSpritesheet("bull_spritesheet.png","bull_spritesheet.plist");
    GameManager::getInstance()-> loadSpritesheet("test_sheet.png","test_sheet.plist");

    
    AnimationLoader::loadData();
    
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    CCScene* scene = TestScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
}

void LoadingScene::loadImage(const char* imageFilename, const char* plistFilename, CCTexture2DPixelFormat texturePixelFormat)
{
    GameManager::getInstance()->loadSpritesheet(imageFilename, plistFilename);
    
    
    //  //  CCTexture2D::setDefaultAlphaPixelFormat(texturePixelFormat);
    //    CCTextureCache::sharedTextureCache()->addImageAsync(imageFilename, this, callfuncO_selector(LoadingScene::finishLoadingResource));
    // //   CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_Default);
    resourceCount++;
}


void LoadingScene::finishLoadingResource(CCObject* object)
{
    CCTexture2D* texture2D = static_cast<CCTexture2D*>(object);
    // texture2D->setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444);
    currResourceCount++;
    if(currResourceCount >= resourceCount)
    {
        
        
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_1.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_2.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_3.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_spritesheet_4.plist");
        ////
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_1.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_2.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("map1_background_spritesheet_3.plist");
        //
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_mass_bomb_spritesheet_2.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_mass_bomb_spritesheet_1.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_lightning_arrow_spritesheet.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_fire_pillar_spritesheet_2.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_fire_pillar_spritesheet_1.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_fire_ball_spritesheet.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_energy_ball_spritesheet.plist");
        //        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("magic_bomb_start_spritesheet.plist");
        
        
        CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
        
        //        CCScene* scene = TestScene::scene();
        //        CCDirector::sharedDirector()->pushScene(scene);
    }
}