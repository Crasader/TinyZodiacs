//
//  ControllerLayer.cpp
//  CharacterDemo
//
//  Created by Nhut on 3/16/14.
//
//

#include "ControllerLayer.h"
#include "Constants.h"

USING_NS_CC;

ControllerLayer * layer;

bool ControllerLayer::init(){
    if(CCLayer::init() == false){
        return false;
    }
    isJumpButtonTouched= false;
    isLeftButtonTouched= false;
    isRightButtonTouched= false;
    
    CCSpriteFrame* temp = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("skill_1_normal.png");
    
    _LeftButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),LEFT_BTN_ID);
    _RightButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),RIGHT_BTN_ID);
    _JumpButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),JUMP_BTN_ID);
    _AtkButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),ATK_BTN_ID);
    _Skill1ButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),SKILL_1_BTN_ID);
    _Skill2ButtonSprite = GameplayButton::create(temp, temp, temp, this, ccp(0,0),SKILL_2_BTN_ID);
    
    TextureSelector leftButtonSelector;
    leftButtonSelector.activeTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("left_normal.png");
    leftButtonSelector.selectedTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("left_selected.png");
    leftButtonSelector.deactiveTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("left_deactive.png");
    _LeftButtonSprite->setTextureSelector(leftButtonSelector);

    TextureSelector rightButtonSelector;
    rightButtonSelector.activeTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("right_normal.png");
    rightButtonSelector.selectedTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("right_selected.png");
    rightButtonSelector.deactiveTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("right_deactive.png");
    _RightButtonSprite->setTextureSelector(rightButtonSelector);
    
    TextureSelector jumpButtonSelector;
    jumpButtonSelector.activeTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_normal.png");
    jumpButtonSelector.selectedTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_selected.png");
    jumpButtonSelector.deactiveTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("jump_deactive.png");
    _JumpButtonSprite->setTextureSelector(jumpButtonSelector);
    
    _LeftButtonSprite->attach();
    _RightButtonSprite->attach();
    _JumpButtonSprite->attach();
    _AtkButtonSprite->attach();
    _Skill1ButtonSprite->attach();
    _Skill2ButtonSprite->attach();
    
//    _RightButtonSprite->getCurrentSprite()->setRotation(180);
//    _AtkButtonSprite->getCurrentSprite()->setRotation(180);

    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(ControllerLayer::update));
        
    return true;
}

ControllerLayer * ControllerLayer::create(cocos2d::CCLayer *containLayer){
    layer = ControllerLayer::create();
    layer-> _ContainerLayer = containLayer;
    
    CCSize sSize = CCDirector::sharedDirector()->getVisibleSize();
    
    float leftX = layer->_LeftButtonSprite->boundingBox().size.width/2;
    float leftY = layer->_LeftButtonSprite->boundingBox().size.height/2 + 10;
    
    float rightX = leftX + layer->_LeftButtonSprite->boundingBox().size.width/2 + layer->_RightButtonSprite->boundingBox().size.width/2 + 10;
    float rightY = leftY;
    
    float atkX = sSize.width - layer->_AtkButtonSprite->boundingBox().size.width/2 -10;
    float atkY = leftY;
    
    float skill1X = atkX;
    float skill1Y = atkY + layer->_Skill1ButtonSprite->boundingBox().size.height/2 + layer->_AtkButtonSprite->boundingBox().size.height/2 + 10;
    
    float skill2X = skill1X - layer->_Skill1ButtonSprite->boundingBox().size.width/2 - layer->_Skill2ButtonSprite->boundingBox().size.width/2 - 10;
    float skill2Y = skill1Y;

    float jumpX = skill2X;
    float jumpY = atkY;
    
    layer->setLeftButtonPosition(leftX, leftY);
    layer->setRightButtonPosition(rightX, rightY);
    layer->setJumpButtonPosition(jumpX, jumpY);
    layer->setAtkButtonPosition(atkX, atkY);
    layer->setSkill1ButtonPosition(skill1X, skill1Y);
    layer->setSkill2ButtonPosition(skill2X, skill2Y);

    
    return layer;
}

ControllerLayer * ControllerLayer::getInstance()
{
    return layer;
}

void ControllerLayer::setJumpButtonPosition(float x, float y){
    _JumpButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::setLeftButtonPosition(float x, float y){
    _LeftButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::setRightButtonPosition(float x, float y){
    _RightButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::setAtkButtonPosition(float x, float y){
    _AtkButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::setSkill1ButtonPosition(float x, float y){
    _Skill1ButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::setSkill2ButtonPosition(float x, float y){
    _Skill2ButtonSprite->changePosition(ccp(x,y));
}

void ControllerLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
    _LeftButtonSprite->ccTouchesBegan(pTouches, event);
    _RightButtonSprite->ccTouchesBegan(pTouches, event);
    _JumpButtonSprite->ccTouchesBegan(pTouches, event);
    _AtkButtonSprite->ccTouchesBegan(pTouches, event);
    _Skill1ButtonSprite->ccTouchesBegan(pTouches, event);
    _Skill2ButtonSprite->ccTouchesBegan(pTouches, event);

}

void ControllerLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    _LeftButtonSprite->ccTouchesMoved(pTouches, event);
    _RightButtonSprite->ccTouchesMoved(pTouches, event);
    _JumpButtonSprite->ccTouchesMoved(pTouches, event);
    _AtkButtonSprite->ccTouchesMoved(pTouches, event);
    _Skill1ButtonSprite->ccTouchesMoved(pTouches, event);
    _Skill2ButtonSprite->ccTouchesMoved(pTouches, event);
}

void ControllerLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
    _LeftButtonSprite->ccTouchesEnded(pTouches, event);
    _RightButtonSprite->ccTouchesEnded(pTouches, event);
    _JumpButtonSprite->ccTouchesEnded(pTouches, event);
    _AtkButtonSprite->ccTouchesEnded(pTouches, event);
    _Skill1ButtonSprite->ccTouchesEnded(pTouches, event);
    _Skill2ButtonSprite->ccTouchesEnded(pTouches, event);
}

void ControllerLayer::update (float dt){
    //Button event update
    _LeftButtonSprite->update(dt);
    _RightButtonSprite->update(dt);
    _JumpButtonSprite->update(dt);
    _AtkButtonSprite->update(dt);
    _Skill1ButtonSprite->update(dt);
    _Skill2ButtonSprite->update(dt);
}

void ControllerLayer::setLeftButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_LeftButtonSprite->setTouchEventHandler(handler);
}

void ControllerLayer::setRightButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_RightButtonSprite->setTouchEventHandler(handler);
}

void ControllerLayer::setJumpButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_JumpButtonSprite->setTouchEventHandler(handler);
}

void ControllerLayer::setAtkButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_AtkButtonSprite->setTouchEventHandler(handler);
}

void ControllerLayer::setSkill1ButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_Skill1ButtonSprite->setTouchEventHandler(handler);
}

void ControllerLayer::setSkill2ButtonEventHadler(iUIObjectTouchEventInterface * handler)
{
    this->_Skill2ButtonSprite->setTouchEventHandler(handler);
}

ControllerLayer::~ControllerLayer() {
    
}