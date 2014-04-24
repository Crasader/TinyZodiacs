//
//  GameMenuLayer.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/9/14.
//
//

#include "GameMenuLayer.h"
#include "GameBackgroundLayer.h"
#include "GameObjectLayer.h"
#include "ControllerLayer.h"

USING_NS_CC;

bool GameMenuLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
//    CCMenuItemImage* pLeftControl = CCMenuItemImage::create("CloseNormal.png",
//                                                            "CloseSelected.png",
//                                                            this, menu_selector(GameMenuLayer::LeftCallBack));
//    
//    CCMenuItemImage* pRightControl = CCMenuItemImage::create("CloseNormal.png",
//                                                             "CloseSelected.png",
//                                                             this, menu_selector(GameMenuLayer::RightCallBack));
//    CCMenuItemImage* pUpControl = CCMenuItemImage::create("CloseNormal.png",
//                                                          "CloseSelected.png",
//                                                          this, menu_selector(GameMenuLayer::UpCallBack));
//    
//    CCMenuItemImage* pDownControl = CCMenuItemImage::create("CloseNormal.png",
//                                                            "CloseSelected.png",
//                                                            this, menu_selector(GameMenuLayer::DownCallBack));
//    pLeftControl->setPosition(ccp(20 ,60));
//    pRightControl->setPosition(ccp(70 ,60));
//    pUpControl->setPosition(ccp(400 ,95));
//    pDownControl->setPosition(ccp(450, 95));
//    
//    CCArray* menuArray = CCArray::create();
//    
//    menuArray->addObject(pLeftControl);
//    menuArray->addObject(pRightControl);
//    menuArray->addObject(pUpControl);
//    menuArray->addObject(pDownControl);
//    
//    
//    
//    CCMenu* menu = CCMenu::createWithArray(menuArray);
//    menu -> setPosition(CCPointZero);
//    
//    this->addChild(menu, 1);
//    
//    joyStick = HSJoystick::create();    
//    joyStick->setPosition(ccp(0,0));
//    this->addChild(joyStick,2);
    
    ControllerLayer * mlayer = ControllerLayer::create(this);
    mlayer->setLeftButtonEventHadler(this);
    mlayer->setRightButtonEventHadler(this);
    mlayer->setJumpButtonEventHadler(this);
    mlayer->setAtkButtonEventHadler(this);
    mlayer->setSkill1ButtonEventHadler(this);
    mlayer->setSkill2ButtonEventHadler(this);

    
    this->addChild(mlayer, 1);
    
    this->setTouchEnabled(true);
    
    
     label = CCLabelTTF::create("0", "Arial", 30);
    label->setPosition(ccp(500,500));
    label->setAnchorPoint(ccp(0,0));
    
    this->addChild(label);
    
    this->scheduleUpdate();

    
    //CONTROLLER
   
    
    //this->addChild(mlayer, 1);

    
    this->setTouchEnabled(true);
    return true;
    
    
    
    
}

void GameMenuLayer::update(float dt)
{
//    float vx = joyStick->getVelocity().x;
//    float vy = joyStick->getVelocity().y;
//    
//    if(this->getParent()->getChildByTag(3)!=NULL)
//        ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSprite(vx*5,vy*5);
    if(this->getParent()->getChildByTag(3)!=NULL)
    {
        label->setString(((GameObjectLayer*)this->getParent()->getChildByTag(3))->text->getCString());
       }

    
    
}


void GameMenuLayer::LeftCallBack(cocos2d::CCObject *sender)
{
    if(this->getParent()->getChildByTag(3)!=NULL)
        ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteLeft();
}

void GameMenuLayer::RightCallBack(cocos2d::CCObject *sender)
{
    if(this->getParent()->getChildByTag(3)!=NULL)
        ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteRight();
}

void GameMenuLayer::UpCallBack(cocos2d::CCObject *sender)
{
    if(this->getParent()->getChildByTag(3)!=NULL)
        ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteUp();
}

void GameMenuLayer::DownCallBack(cocos2d::CCObject *sender)
{
    if(this->getParent()->getChildByTag(3)!=NULL)
        ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteDown();
}

void GameMenuLayer::touchBegan(void* sender ,CCSet* pTouches, CCEvent* event)
{
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteUp();

    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->Attack();

    }
    else if(id.compare(SKILL_1_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->Skill1();
        
    }
    else if(id.compare(SKILL_2_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->Skill2();
        
    }
}
void GameMenuLayer::touchHold(void* sender ,CCSet* pTouches, CCEvent* event)
{
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteLeft();
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteRight();
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
        

    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
//        if(this->getParent()->getChildByTag(3)!=NULL)
//            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->Attack();
//        if(this->getParent()->getChildByTag(3)!=NULL)
//            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteRight();

    }
}
void GameMenuLayer::touchEnded(void* sender ,CCSet* pTouches, CCEvent* event)
{
    ;
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
            ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteDown();
        
       
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
        if(this->getParent()->getChildByTag(3)!=NULL)
           ((GameObjectLayer*)this->getParent()->getChildByTag(3))->MoveSpriteDown();
        
       
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
    }
}

void GameMenuLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
//    CCTouch* touch = (CCTouch*)pTouches->anyObject();
//    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()) ;
//    
//    
//    label->setString(CCString::createWithFormat("%0.2f-%0.2f",touchPoint.x,touchPoint.y)->getCString());
}

