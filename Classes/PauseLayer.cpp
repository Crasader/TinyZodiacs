//
//  PauseLayer.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/18/14.
//
//

#include "PauseLayer.h"
#include "ControllerManager.h"

using cocos2d::gui::SEL_TouchEvent;

PauseLayer::PauseLayer()
{
    
}

PauseLayer::~PauseLayer()
{
    
}

void PauseLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    this->mainPanel = (cocos2d::gui::UIPanel*)ul->getChildByName("main_panel");
    
    this->btnQuit = (cocos2d::gui::UIButton*)ul->getChildByName("main_panel")->getChildByName("controller_panel")->getChildByName("quit_button");
    this->btnResume = (cocos2d::gui::UIButton*)ul->getChildByName("main_panel")->getChildByName("controller_panel")->getChildByName("resume_button");

    this->btnQuit->addTouchEventListener(this, toucheventselector(PauseLayer::quitButtonTouchEvent));
    this->btnResume->addTouchEventListener(this, toucheventselector(PauseLayer::resumeButtonTouchEvent));
    
    this->mainPanel->setPositionType(cocos2d::gui::POSITION_ABSOLUTE);
    this->mainPanel->setPositionX(CCDirector::sharedDirector()->getWinSize().width/2-this->mainPanel->getSize().width/2);
}


bool PauseLayer::init()
{
    if(!cocos2d::gui::TouchGroup::init())
    {
        return false;
    }
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("PauseLayer.ExportJson");
    
    this->addWidget(ul);
    
    loadAllUI(ul);
    
    playInAnimation();
    
    return true;
}

void PauseLayer::resumeButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            this->playOutAnimation(false);
            break;
        }
        default:
            break;
    }
}

void PauseLayer::quitButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            this->playOutAnimation(true);
            break;
        }
        default:
            break;
    }
}

void PauseLayer::playInAnimation()
{
    CCMoveTo* moveToAnimation1 = CCMoveTo::create(0.5f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y-5));
    CCMoveTo* moveToAnimation2 = CCMoveTo::create(0.2f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y+5));
    CCMoveTo* moveToAnimation3 = CCMoveTo::create(0.1f, this->mainPanel->getPosition());
    CCArray * array = CCArray::create();
    array->addObject(moveToAnimation1);
    array->addObject(moveToAnimation2);
    array->addObject(moveToAnimation3);
    CCSequence* animation = CCSequence::create(array);
    this->mainPanel->setPositionY(CCDirector::sharedDirector()->getWinSize().height + this->mainPanel->getSize().height);
    this->mainPanel->runAction(animation);
}

void PauseLayer::playOutAnimation(bool shouldQuit)
{
    CCMoveTo* moveToAnimation1 = CCMoveTo::create(0.1f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y-5));
    CCMoveTo* moveToAnimation2 = CCMoveTo::create(0.2f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y+5));
    CCMoveTo* moveToAnimation3 = CCMoveTo::create(0.5f, ccp(this->mainPanel->getPosition().x,CCDirector::sharedDirector()->getWinSize().height + this->mainPanel->getSize().height));
    CCArray * array = CCArray::create();
    array->addObject(moveToAnimation1);
    array->addObject(moveToAnimation2);
    array->addObject(moveToAnimation3);
    
    if(shouldQuit == false)
    {
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(PauseLayer::detachFromParent));
        array->addObject(call);
    }
    else
    {
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(PauseLayer::detachFromParentAndQuit));
        array->addObject(call);
    }
    
    CCSequence* animation = CCSequence::create(array);
    this->mainPanel->runAction(animation);
}

void PauseLayer::detachFromParent()
{
    this->removeFromParent();
}

void PauseLayer::detachFromParentAndQuit()
{
    detachFromParent();
    ControllerManager::getInstance()->sendCommand(GAME_MATCH_CONTROLLER,  QUIT_GAME);
}