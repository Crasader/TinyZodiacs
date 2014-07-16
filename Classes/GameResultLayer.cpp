//
//  GameResultLayer.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/16/14.
//
//

#include "GameResultLayer.h"
#include "ControllerManager.h"
#include "XMLButtonSelectorParser.h"

using cocos2d::gui::SEL_TouchEvent;

GameResultLayer::GameResultLayer()
{
    
}

GameResultLayer::~GameResultLayer()
{
    
}

void GameResultLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    this->setTouchPriority(100);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->mainPanel = cocos2d::gui::Layout::create();
    
    this->mainPanel->setPosition(size/2);
    this->mainPanel->setSize(size*(3.0f/4));
    
    this->mainPanel->setBackGroundImageScale9Enabled(true);
    this->mainPanel->setBackGroundImage("panel_2.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
    //
    //    this->mainPanel->setBackGroundColorType(cocos2d::gui::LAYOUT_COLOR_SOLID);
    //    this->mainPanel->setBackGroundColor(ccc3(255, 0, 0));
    this->mainPanel->setAnchorPoint(ccp(0.5f,0.5f));
    
    
    cocos2d::gui::Layout* darkColorLayout = cocos2d::gui::Layout::create();
    darkColorLayout->setBackGroundColorType(cocos2d::gui::LAYOUT_COLOR_SOLID);
    darkColorLayout->setBackGroundColor(ccc3(10, 10, 10));
    darkColorLayout->setBackGroundColorOpacity(150);
    darkColorLayout->setSize(size);
    darkColorLayout->setPosition(ccp(0,0));
    darkColorLayout->setTouchEnabled(true);
    
    //BUTTON QUIT
    
    this->btnQuit = cocos2d::gui::Button::create();
    this->btnQuit->setAnchorPoint(ccp(1,0));
    this->btnQuit->setPosition(ccp(mainPanel->getSize().width-50, 50));
    this->btnQuit->setTouchEnabled(true);
    this->btnQuit->addTouchEventListener(this, toucheventselector(GameResultLayer::quitButtonTouchEvent));
    
    TextureSelector textureSelector = XMLButtonSelectorParser::parseData("quit_button");
    this->btnQuit->loadTextures(textureSelector.activeTexture.c_str(), textureSelector.selectedTexture.c_str(), textureSelector.deactiveTexture.c_str(), cocos2d::gui::UI_TEX_TYPE_PLIST);
    this->btnQuit->setScale((this->mainPanel->getSize().height/7.0f)/this->btnQuit->getSize().height);
    this->mainPanel->addChild(this->btnQuit);
    
    ul->addChild(darkColorLayout,0);
    ul->addChild(this->mainPanel,1);
}


bool GameResultLayer::init()
{
    if(!cocos2d::gui::TouchGroup::init())
    {
        return false;
    }
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    
    this->addWidget(ul);
    
    loadAllUI(ul);
    
    playInAnimation();
    
    return true;
}

void GameResultLayer::restartButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
        }
            break;
        default:
            break;
    }
}

void GameResultLayer::quitButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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

void GameResultLayer::playInAnimation()
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

void GameResultLayer::playOutAnimation(bool shouldQuit)
{
    CCMoveTo* moveToAnimation1 = CCMoveTo::create(0.05f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y-5));
    CCMoveTo* moveToAnimation2 = CCMoveTo::create(0.1f, ccp(this->mainPanel->getPosition().x,this->mainPanel->getPosition().y+5));
    CCMoveTo* moveToAnimation3 = CCMoveTo::create(0.25f, ccp(this->mainPanel->getPosition().x,CCDirector::sharedDirector()->getWinSize().height + this->mainPanel->getSize().height));
    CCArray * array = CCArray::create();
    array->addObject(moveToAnimation1);
    array->addObject(moveToAnimation2);
    array->addObject(moveToAnimation3);
    
    if(shouldQuit == false)
    {
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameResultLayer::detachFromParent));
        array->addObject(call);
    }
    else
    {
        CCCallFunc* call = CCCallFunc::create(this, callfunc_selector(GameResultLayer::detachFromParentAndQuit));
        array->addObject(call);
    }
    
    CCSequence* animation = CCSequence::create(array);
    this->mainPanel->runAction(animation);
}

void GameResultLayer::detachFromParent()
{
    this->removeFromParent();
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, RESUME_GAME);
}

void GameResultLayer::detachFromParentAndQuit()
{
    detachFromParent();
    ControllerManager::getInstance()->sendCommand(GAME_MATCH_CONTROLLER, QUIT_GAME);
}

void GameResultLayer::setTime(int time)
{
    CCString* timeText = CCString::createWithFormat("Time: %d", time);
    this->lblTime->setText(timeText->getCString());
}

void GameResultLayer::setHightScore(int score)
{
    CCString* highscoreText = CCString::createWithFormat("HighScore: %d", score);
    this->lblHightScore->setText(highscoreText->getCString());
}

void GameResultLayer::setScore(int score)
{
    CCString* scoreText = CCString::createWithFormat("Score: %d", score);
    this->lblScore->setText(scoreText->getCString());
    
    int highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("map1-highscore", 0);
    
    if(score > highscore)
    {
        setHightScore(score);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("map1-highscore", score);
    }
    
}

void GameResultLayer::setResult(bool win, Achievement* achievement)
{
    if(win)
    {
        loadUIWin();
        if(achievement != NULL)
        {
            setScore(achievement->getScore());
            setTime(achievement->getTime());
            int highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey("map1-highscore", 0);
            setHightScore(highscore);
        }
    }
    else
    {
        loadUILose();
    }
}

void GameResultLayer::loadUIWin()
{
    //IMAGE VIEW WIN
    cocos2d::gui::ImageView* failedImage = cocos2d::gui::ImageView::create();
    failedImage->loadTexture("victory_title.png", cocos2d::gui::UI_TEX_TYPE_PLIST);
    failedImage->setPosition(ccp(this->mainPanel->getSize().width/2,this->mainPanel->getSize().height - 100));
    this->mainPanel->addChild(failedImage);
    
    //TIME LABEL
    this->lblTime = cocos2d::gui::Label::create();
    this->lblTime->setFontName("Marker Felt");
    this->lblTime->setAnchorPoint(ccp(0,0.5f));
    this->lblTime->setText("Time: 1m52s");
    this->lblTime->setColor(ccc3(255,255,255));
    this->lblTime->setPosition(ccp(100,this->mainPanel->getSize().height - 220));
    this->lblTime->setFontSize(50);
    this->mainPanel->addChild(lblTime);
    
    //SCORE LABEL
    this->lblScore = cocos2d::gui::Label::create();
    this->lblScore->setFontName("Marker Felt");
    this->lblScore->setAnchorPoint(ccp(0,0.5f));
    this->lblScore->setText("Score: 25550");
    this->lblScore->setColor(ccc3(255,255,255));
    this->lblScore->setPosition(ccp(100,this->lblTime->getPosition().y - 70));
    this->lblScore->setFontSize(50);
    this->mainPanel->addChild(lblScore);
    //SCORE LABEL
    this->lblHightScore = cocos2d::gui::Label::create();
    this->lblHightScore->setFontName("Marker Felt");
    this->lblHightScore->setAnchorPoint(ccp(0,0.5f));
    this->lblHightScore->setText("HightScore: 25550");
    this->lblHightScore->setColor(ccc3(255,255,255));
    this->lblHightScore->setPosition(ccp(100,this->lblScore->getPosition().y - 70));
    this->lblHightScore->setFontSize(50);
    this->mainPanel->addChild(lblHightScore);
    
}

void GameResultLayer::loadUILose()
{
    cocos2d::gui::ImageView* failedImage = cocos2d::gui::ImageView::create();
    failedImage->loadTexture("gameover_title.png", cocos2d::gui::UI_TEX_TYPE_PLIST);
    failedImage->setPosition(ccp(this->mainPanel->getSize().width/2,this->mainPanel->getSize().height - 100));
    failedImage->setScale(1.5f);
    this->mainPanel->addChild(failedImage);
    
    cocos2d::gui::ImageView* deadImage = cocos2d::gui::ImageView::create();
    deadImage->loadTexture("willbeback.png", cocos2d::gui::UI_TEX_TYPE_PLIST);
    deadImage->setPosition(ccp(this->mainPanel->getSize().width/2 -170,this->mainPanel->getSize().height/2-100));
    deadImage->setScale(2.0f);
    
    this->mainPanel->addChild(deadImage);
    
}