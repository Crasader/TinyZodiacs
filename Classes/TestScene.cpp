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
#include "AnimationFactory.h"
#include "GameManager.h"
#include "GameBackgroundLayer.h"
#include "GameObjectLayer.h"
#include "GameMenuLayer.h"

USING_NS_CC;

bool TestScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    CCMenuItemImage *pMenuBack = CCMenuItemImage::create("CloseNormal.png",
                                                         "CloseSelected.png",
                                                         this,
                                                         menu_selector(TestScene::menuBackCallBack));
    pMenuBack->setPosition(ccp(20 ,20));
    
    
    CCMenu *menuBack = CCMenu::create(pMenuBack,NULL);
    
    menuBack->setPosition(CCPointZero);
 //   this->addChild(menuBack, 1);
    
    GameManager::getSharedManager()->loadResource();
    initScene();
    
    
    return true;
}
CCScene* TestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestScene *layer = TestScene::create();
    
    
    
    // add layer as a child to scene
    scene->addChild(layer);
  

    
    
    GameObjectLayer* objectLayer = GameObjectLayer::create();
    scene->addChild(objectLayer, 1, 3);
    
    GameMenuLayer* menuLayer = GameMenuLayer::create();
    scene->addChild(menuLayer, 1, 4);
    
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
