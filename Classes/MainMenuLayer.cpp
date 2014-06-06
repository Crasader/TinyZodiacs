//
//  MainMenuLayer.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/5/14.
//
//

#include "MainMenuLayer.h"
#include "TestScene.h"
#include "GameManager.h"


using cocos2d::gui::SEL_TouchEvent;

MainMenuLayer::MainMenuLayer()
{
    
}

MainMenuLayer::~MainMenuLayer()
{
}

CCScene* MainMenuLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuLayer *layer = MainMenuLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MainMenuLayer* MainMenuLayer::layer()
{
    // 'layer' is an autorelease object
    MainMenuLayer *layer = MainMenuLayer::create();
    return layer;
}

bool MainMenuLayer::init()
{
    if(!cocos2d::gui::TouchGroup::init())
    {
        return false;
    }
    //
    GameManager::getInstance()->loadResource();
    GameManager::getInstance()->loadData();
    GameManager::getInstance()->initManager();
    //
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("MainMenuLayer_1.ExportJson");
    
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
    
    loadAllUI(ul);
    
    this->addWidget(ul);
    return true;
}

void MainMenuLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    this->backgroundLayer = (cocos2d::gui::ImageView*)(ul->getChildByName("background_image"));
    
    this->btnPlay = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("play_button");
    this->btnInfo = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("info_button");
    this->btnOption = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("option_button");
    
    this->btnPlay->addTouchEventListener(this, toucheventselector(MainMenuLayer::playButtonTouchEvent));
    this->btnInfo->addTouchEventListener(this, toucheventselector(MainMenuLayer::infoButtonTouchEvent));
    this->btnOption->addTouchEventListener(this, toucheventselector(MainMenuLayer::optionButtonTouchEvent));
}

void MainMenuLayer::playButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
            CCScene* testScene = TestScene::scene();
            CCDirector::sharedDirector()->pushScene(testScene);
        }
            break;
        default:
            break;
    }
}

void MainMenuLayer::infoButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            break;
        default:
            break;
    }

}

void MainMenuLayer::optionButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            break;
        default:
            break;
    }

}
