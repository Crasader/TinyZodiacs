//
//  HeroSelectScene.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#include "HeroSelectScene.h"
#include "ResourceLoader.h"

bool HeroSelectScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    initScene();
    this->resourcePack = XMLResourcePackParser::getResourcePackInFile("heroselection_resource", "resource_list.xml");
    this->resourcePack->retain();
    ResourceLoader::loadResourcePack(this->resourcePack);
    return true;
}


HeroSelectScene::~HeroSelectScene()
{
    ResourceLoader::unloadResourcePack(this->resourcePack);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    this->resourcePack->release();
}

CCScene* HeroSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HeroSelectScene *layer = HeroSelectScene::create();
    // add layer as a child to scene
    scene->addChild(layer,0,1);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);

    // return the scene
    return scene;
}


void HeroSelectScene::initScene()
{
    loadResource();
    HeroSelectLayer* layer = HeroSelectLayer::create();
    this->addChild(layer);
    
    
}

void HeroSelectScene::loadResource()
{
    this->resourcePack = XMLResourcePackParser::getResourcePackInFile("heroselection_resource", "resource_list.xml");
    this->resourcePack->retain();
    ResourceLoader::loadResourcePack(this->resourcePack);
}
