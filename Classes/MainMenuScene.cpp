//
//  MainMenuScene.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/5/14.
//
//

#include "MainMenuScene.h"
#include "MainMenuLayer.h"
#include "SoundManager.h"
#include "ResourcePack.h"
#include "ResourceLoader.h"

bool MainMenuScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    ResourcePack* resourcePack = XMLResourcePackParser::getResourcePackInFile("mainmenu_resource", "resource_list.xml");
    ResourceLoader::loadResourcePack(resourcePack);
    initScene();
   
    
    return true;
}


MainMenuScene::~MainMenuScene()
{

}

CCScene* MainMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);
    
    // return the scene
    return scene;
}

void MainMenuScene::menuBackCallBack(cocos2d::CCObject *pSender)
{

}

void MainMenuScene::initScene()
{
    MainMenuLayer* layer = MainMenuLayer::create();
    this->addChild(layer);
    
    SoundManager::playMenuMusic();
//    CCParticleSystemQuad* p = CCParticleSystemQuad::create("starSky.plist");
//    p->setPosition(0,0);
//    p->setRotation(0);
//    this->addChild(p);
}
