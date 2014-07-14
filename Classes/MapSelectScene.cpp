//
//  MapSelectScene.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "MapSelectScene.h"
#include "MapSelectLayer.h"

bool MapSelectScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    //CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    initScene();
    return true;
}


MapSelectScene::~MapSelectScene()
{
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("MapListItem0.png");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("MapSelectScene0.png");
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
//    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

CCScene* MapSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MapSelectScene *layer = MapSelectScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);
    
    // return the scene
    return scene;
}


void MapSelectScene::initScene()
{
    MapSelectLayer* layer = MapSelectLayer::create();
    this->addChild(layer);
}
