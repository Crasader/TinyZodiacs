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
    initScene();
    return true;
}


MapSelectScene::~MapSelectScene()
{
    
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

void MapSelectScene::menuBackCallBack(cocos2d::CCObject *pSender)
{
    
}

void MapSelectScene::initScene()
{
    MapSelectLayer* layer = MapSelectLayer::layer();
    this->addChild(layer);
}
