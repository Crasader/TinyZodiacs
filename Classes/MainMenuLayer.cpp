//
//  MainMenuLayer.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/5/14.
//
//

#include "MainMenuLayer.h"
#include "MapSelectScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "UIConstant.h"


using cocos2d::gui::SEL_TouchEvent;
using cocos2d::gui::ListViewGravity;

MainMenuLayer::MainMenuLayer()
{
    
}

MainMenuLayer::~MainMenuLayer()
{
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("MainMenuLayer0.png");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
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
    
//
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
//
    ul->setTouchEnabled(true);
    loadAllUI(ul);
    this->addWidget(ul);
    
      CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    return true;
}

void MainMenuLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    this->backgroundLayer = (cocos2d::gui::ImageView*)(ul->getChildByName("background_image"));
    
    this->optionPanel = (cocos2d::gui::UIPanel*)(ul->getChildByName("background_image")->getChildByName("option_panel"));
    this->inforPanel = (cocos2d::gui::UIPanel*)(ul->getChildByName("background_image")->getChildByName("info_panel"));
    
    this->btnPlay = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("play_button");
    this->btnInfo = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("info_button");
    this->btnOption = (cocos2d::gui::Button*)this->backgroundLayer->getChildByName("option_button");
    
    this->btnMusic = (cocos2d::gui::Button*)(ul->getChildByName("background_image")->getChildByName("option_panel")->getChildByName("music_button"));
    this->btnSound = (cocos2d::gui::Button*)(ul->getChildByName("background_image")->getChildByName("option_panel")->getChildByName("sound_button"));

    this->btnFacebook = (cocos2d::gui::Button*)(ul->getChildByName("background_image")->getChildByName("info_panel")->getChildByName("facebook_button"));
    this->btnGooglePlus = (cocos2d::gui::Button*)(ul->getChildByName("background_image")->getChildByName("info_panel")->getChildByName("google_plus_button"));

    
    this->btnPlay->addTouchEventListener(this, toucheventselector(MainMenuLayer::playButtonTouchEvent));
    this->btnInfo->addTouchEventListener(this, toucheventselector(MainMenuLayer::infoButtonTouchEvent));
    this->btnOption->addTouchEventListener(this, toucheventselector(MainMenuLayer::optionButtonTouchEvent));
    
    this->btnMusic->addTouchEventListener(this, toucheventselector(MainMenuLayer::musicButtonTouchEvent));
    this->btnSound->addTouchEventListener(this, toucheventselector(MainMenuLayer::soundButtonTouchEvent));

    this->btnFacebook->addTouchEventListener(this, toucheventselector(MainMenuLayer::facebookButtonTouchEvent));
    this->btnGooglePlus->addTouchEventListener(this, toucheventselector(MainMenuLayer::googleplusButtonTouchEvent));
    
    //Get scale
    soundBtnScale = this->btnSound->getScale();
    musicButtonScale = this->btnMusic->getScale();
    fbBtnScale = this->btnFacebook->getScale();
    gpBtnScale = this->btnGooglePlus->getScale();
    
    //GetPosition
    soundBtnPosition = this->btnSound->getPosition();
    musicButtonPosition = this->btnMusic->getPosition();
    fbBtnPosition = this->btnFacebook->getPosition();
    gpBtnPosition = this->btnGooglePlus->getPosition();


    //Load sound data
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY, false) == false)
    {
        this->btnSound->loadTextures("sound_off.png", "sound_off_selected.png", "sound_off.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    }
    else
    {
        this->btnSound->loadTextures("sound.png", "sound_selected.png", "sound.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
    }
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY, false) == false)
    {
        this->btnMusic->loadTextures("music_off.png", "music_off_selected.png", "music_off.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    }
    else
    {
        this->btnMusic->loadTextures("music.png", "music_selected.png", "music.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
    }
    //
    this->isInforShown = this->isOPtionShown = false;
    this->btnFacebook->setPositionY(this->inforPanel->getPositionY());
    this->btnGooglePlus->setPositionY(this->inforPanel->getPositionY());

    this->btnSound->setPositionY(this->optionPanel->getPositionY());
    this->btnMusic->setPositionY(this->optionPanel->getPositionY());

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
            this->btnMusic->stopAllActions();
            this->btnSound->stopAllActions();

            this->btnFacebook->stopAllActions();
            this->btnGooglePlus->stopAllActions();
            
            //
            this->isInforShown = this->isOPtionShown = false;
            this->btnFacebook->setPositionY(this->inforPanel->getPositionY());
            this->btnGooglePlus->setPositionY(this->inforPanel->getPositionY());
            
            this->btnSound->setPositionY(this->optionPanel->getPositionY());
            this->btnMusic->setPositionY(this->optionPanel->getPositionY());

            
            CCScene* testScene = MapSelectScene::scene();
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
        {
            this->btnFacebook->stopAllActions();
            this->btnGooglePlus->stopAllActions();
            
            this->btnFacebook->runAction(this->initButtonAnimation(this->btnFacebook,this->btnInfo, this->fbBtnPosition, this->fbBtnScale, !this->isInforShown));
            this->btnGooglePlus->runAction(this->initButtonAnimation(this->btnGooglePlus,this->btnInfo, this->gpBtnPosition, this->gpBtnScale, !this->isInforShown));
            this->isInforShown = !this->isInforShown;
        }            break;
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
            {
                this->btnMusic->stopAllActions();
                this->btnSound->stopAllActions();
                
                this->btnMusic->runAction(this->initButtonAnimation(this->btnMusic,this->btnOption, this->musicButtonPosition, this->musicButtonScale, !this->isOPtionShown));
                this->btnSound->runAction(this->initButtonAnimation(this->btnSound,this->btnOption, this->soundBtnPosition, this->soundBtnScale, !this->isOPtionShown));
                this->isOPtionShown = !this->isOPtionShown;
            }
            break;
        default:
            break;
    }
    
}

void MainMenuLayer::soundButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            if(CCUserDefault::sharedUserDefault()->getBoolForKey(SOUND_KEY, true))
            {
                this->btnSound->loadTextures("sound_off.png", "sound_off_selected.png", "sound_off.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
                CCUserDefault::sharedUserDefault()->setBoolForKey(SOUND_KEY, false);
            }
            else
            {
                this->btnSound->loadTextures("sound.png", "sound_selected.png", "sound.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
                CCUserDefault::sharedUserDefault()->setBoolForKey(SOUND_KEY, true);
            }
            break;
        default:
            break;
    }
}

void MainMenuLayer::musicButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            if(CCUserDefault::sharedUserDefault()->getBoolForKey(MUSIC_KEY, true))
            {
                this->btnMusic->loadTextures("music_off.png", "music_off_selected.png", "music_off.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
                CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, false);
            }
            else
            {
                this->btnMusic->loadTextures("music.png", "music_selected.png", "music.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
                CCUserDefault::sharedUserDefault()->setBoolForKey(MUSIC_KEY, true);
            }
            break;
        default:
            break;
    }
}

void MainMenuLayer::facebookButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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

void MainMenuLayer::googleplusButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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

CCAction* MainMenuLayer::initButtonAnimation(cocos2d::gui::Widget* target, cocos2d::gui::Widget* parent, CCPoint originalPosition, float originalScale, bool isIn)
{
    float duration = 1.15f;
    
    CCMoveTo* moveToAction;
    CCRotateTo* rotateAction;
    CCScaleTo* scaleAction;
    
    if(isIn)
    {
        moveToAction = CCMoveTo::create(duration-0.05, originalPosition);
        rotateAction = CCRotateTo::create(duration, 0);
        scaleAction = CCScaleTo::create(duration, originalScale);
        
        target->setPosition(ccp(target->getPositionX(), parent->getPositionY()+10));
        target->setScale(0);
        target->setRotation(270);
    }
    else
    {
        moveToAction = CCMoveTo::create(duration-0.15, ccp(target->getPositionX(), parent->getPositionY()));
        rotateAction = CCRotateTo::create(duration, 270);
        scaleAction = CCScaleTo::create(duration, 0);
//        target->setPosition(ccp(target->getPositionX(), parent->getPositionY()));
        target->setScale(originalScale);
    }
    CCArray* arr = CCArray::create();
    arr->addObject(moveToAction);
    arr->addObject(rotateAction);
    arr->addObject(scaleAction);
    CCSpawn* action = CCSpawn::create(arr);
    return action;
}

void MainMenuLayer::setOptionPanelVisibilityValue()
{
    this->isOPtionShown = !this->isOPtionShown;
}

void MainMenuLayer::setInforPanelVisibilityValue()
{
    this->isInforShown = !this->isInforShown;
}

void MainMenuLayer::playOptionItemAnimation(CCNode* sender, void* data)
{
    CCArray* animationArray = (CCArray*)data;
    this->btnMusic->runAction((CCAction*)animationArray->objectAtIndex(0));
    this->btnSound->runAction((CCAction*)animationArray->objectAtIndex(1));
}

void MainMenuLayer::playInforItemAnimation(CCNode* sender, void* data)
{
    CCArray* animationArray = (CCArray*)data;
    this->btnFacebook->runAction((CCAction*)animationArray->objectAtIndex(0));
    this->btnGooglePlus->runAction((CCAction*)animationArray->objectAtIndex(1));
}