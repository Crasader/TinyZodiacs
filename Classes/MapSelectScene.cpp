//
//  MapSelectScene.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "MapSelectScene.h"
#include "MapSelectLayer.h"
#include "ResourceLoader.h"
#include "XMLResourcePackParser.h"

bool MapSelectScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    this->resourcePack = XMLResourcePackParser::getResourcePackInFile("mapselection_resource", "resource_list.xml");
    this->resourcePack->retain();
    ResourceLoader::loadResourcePack(resourcePack);
    initScene();
    return true;
}

MapSelectScene::MapSelectScene()
{
    
}

MapSelectScene::~MapSelectScene()
{
    ResourceLoader::unloadResourcePack(this->resourcePack);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    this->resourcePack->release();
}

CCScene* MapSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MapSelectScene *layer = MapSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    MapSelectLayer* maplayer = MapSelectLayer::create();
    scene->addChild(maplayer);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("test.mp3", true);
    
    // return the scene
    return scene;
}


void MapSelectScene::initScene()
{
    
}

void MapSelectScene::unloadResource()
{
    ResourceLoader::unloadResourcePack(this->resourcePack);
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}
