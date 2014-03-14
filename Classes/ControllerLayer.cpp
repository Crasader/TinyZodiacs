//
//  ControllerLayer.cpp
//  CharacterDemo
//
//  Created by Nhut on 3/16/14.
//
//

#include "ControllerLayer.h"

USING_NS_CC;

bool ControllerLayer::init(){
    if(CCLayer::init() == false){
        return false;
    }
    isJumpButtonTouched= false;
    isLeftButtonTouched= false;
    isRightButtonTouched= false;
    
    
    LEFT_BTN_SPRITE = "2.png";
    RIGHT_BTN_SPRITE = "2.png";
    JUMP_BTN_SPRITE = "1.png";
    
    /* Create Image */
    CCImage *LImage = new CCImage();
    LImage->initWithImageFile(LEFT_BTN_SPRITE); /*the pngName is an image file in your resource folder */
    
    /* Create Texture from Image */
    CCTexture2D *LTexture = new CCTexture2D();
    LTexture->initWithImage(LImage);
    
    /* Create Image */
    CCImage *RImage = new CCImage();
    RImage->initWithImageFile(RIGHT_BTN_SPRITE); /*the pngName is an image file in your resource folder */
    
    /* Create Texture from Image */
    CCTexture2D *RTexture = new CCTexture2D();
    RTexture->initWithImage(RImage);
    
    /* Create Image */
    CCImage *JImage = new CCImage();
    JImage->initWithImageFile(JUMP_BTN_SPRITE); /*the pngName is an image file in your resource folder */
    
    /* Create Texture from Image */
    CCTexture2D *JTexture = new CCTexture2D();
    JTexture->initWithImage(JImage);
    
    _LeftButtonSprite = GameplayButton::create(LTexture, LTexture, LTexture, this, ccp(0,0),LEFT_BTN_ID);
    _RightButtonSprite = GameplayButton::create(RTexture, RTexture, RTexture, this, ccp(0,0),RIGHT_BTN_ID);
    _JumpButtonSprite = GameplayButton::create(JTexture, JTexture, JTexture, this, ccp(0,0),JUMP_BTN_ID);
    _AtkButtonSprite = GameplayButton::create(JTexture, JTexture, JTexture, this, ccp(0,0),ATK_BTN_ID);

    
    _LeftButtonSprite->attach();
    _RightButtonSprite->attach();
    _JumpButtonSprite->attach();
    _AtkButtonSprite->attach();
    
    _RightButtonSprite->getCurrentSprite()->setRotation(180);
    _AtkButtonSprite->getCurrentSprite()->setRotation(180);

    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(ControllerLayer::update));
        
    return true;
}

ControllerLayer * ControllerLayer::create(cocos2d::CCLayer *containLayer){
    ControllerLayer * layer = ControllerLayer::create();
    layer-> _ContainerLayer = containLayer;
    
    CCSize sSize = CCDirector::sharedDirector()->getVisibleSize();
    
    float leftX = layer->_LeftButtonSprite->boundingBox().size.width/2;
    float leftY = layer->_LeftButtonSprite->boundingBox().size.height/2;
    
    float rightX = leftX + layer->_LeftButtonSprite->boundingBox().size.width/2 + layer->_RightButtonSprite->boundingBox().size.width/2 + 10;
    float rightY = leftY;
    
    float atkX = sSize.width - layer->_JumpButtonSprite->boundingBox().size.width/2 -10;
    float atkY = leftY;
    
    float jumpX = atkX  - layer->_JumpButtonSprite->boundingBox().size.width/2 - layer->_AtkButtonSprite->boundingBox().size.width/2 - 10;
    float jumpY = leftY;
    
    layer->setLeftButtonPosition(leftX, leftY);
    layer->setRightButtonPosition(rightX, rightY);
    layer->setJumpButtonPosition(jumpX, jumpY);
    layer->setAtkButtonPosition(atkX, atkY);
    
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


void ControllerLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {
    _LeftButtonSprite->ccTouchesBegan(pTouches, event);
    _RightButtonSprite->ccTouchesBegan(pTouches, event);
    _JumpButtonSprite->ccTouchesBegan(pTouches, event);
    _AtkButtonSprite->ccTouchesBegan(pTouches, event);

}

void ControllerLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event){
    _LeftButtonSprite->ccTouchesMoved(pTouches, event);
    _RightButtonSprite->ccTouchesMoved(pTouches, event);
    _JumpButtonSprite->ccTouchesMoved(pTouches, event);
    _AtkButtonSprite->ccTouchesMoved(pTouches, event);

}

void ControllerLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event){
    _LeftButtonSprite->ccTouchesEnded(pTouches, event);
    _RightButtonSprite->ccTouchesEnded(pTouches, event);
    _JumpButtonSprite->ccTouchesEnded(pTouches, event);
    _AtkButtonSprite->ccTouchesEnded(pTouches, event);
}

void ControllerLayer::update (float dt){
    //Button event update
    _LeftButtonSprite->update(dt);
    _RightButtonSprite->update(dt);
    _JumpButtonSprite->update(dt);
    _AtkButtonSprite->update(dt);

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

ControllerLayer::~ControllerLayer() {
    
}