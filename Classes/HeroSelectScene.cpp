//
//  HeroSelectScene.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#include "HeroSelectScene.h"

bool HeroSelectScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    initScene();
    return true;
}


HeroSelectScene::~HeroSelectScene()
{
    
}

CCScene* HeroSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HeroSelectScene *layer = HeroSelectScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);
    
    // return the scene
    return scene;
}


void HeroSelectScene::initScene()
{
    HeroSelectLayer* layer = HeroSelectLayer::create();
    this->addChild(layer);
}
