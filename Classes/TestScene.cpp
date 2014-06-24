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
    
    initScene();
    if(GameManager::getInstance()->getParent() == NULL)
    {
            this->addChild(GameManager::getInstance());
    }
    return true;
}

TestScene::~TestScene()
{
    ControllerManager::getInstance()->clean();
    RuleManager::getInstance()->clean();
    
    SoundManager::playMenuMusic();
}

CCScene* TestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestScene *layer = TestScene::create();
    
    
    
    // add layer as a child to scene
    scene->addChild(layer);
  
    GameplayLayer* menuLayer = GameplayLayer::create();
    scene->addChild(menuLayer, GAME_MENU_LAYER, 4);
    
    GameObjectLayer* objectLayer = GameObjectLayer::create();
    scene->addChild(objectLayer, GAME_OBJECT_LAYER, 3);
    
    // return the scene
    return scene;
}

void TestScene::menuBackCallBack(cocos2d::CCObject *pSender)
{
    
    
    //    CCSprite* testSprite = CCSprite::createWithSpriteFrameName("Walk_LB_1.png");
    //    testSprite->setPosition(ccp(200,200));
    //
    //    this->addChild(testSprite);
    //
    //    CCAnimation* walkAnimation = AnimationFactory::getSharedFactory()->getAnimationByName("etna-Walk_LB");
    //    walkAnimation->setLoops(-1);
    //    CCAnimate* walkiAnimate= CCAnimate::create(walkAnimation);
    //
    //    testSprite->runAction(walkiAnimate);
    
   // if(this->getChildByTag(2)!=NULL)
        //((GameBackgroundLayer*)this->getChildByTag(2))->scrollBackground();
    
    
}

void TestScene::initScene()
{
  
    
}
