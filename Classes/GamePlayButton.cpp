//
//  GamePlayButton.cpp
//  CharacterDemo
//
//  Created by Nhut on 3/20/14.
//
//

#include "GamePlayButton.h"
GameplayButton::GameplayButton(CCTexture2D * enableTexture, CCTexture2D * disableTexture, CCTexture2D * touchedTexture, CCLayer* containLayer, CCPoint position, std::string ID){
    this->_enableTexture = enableTexture;
    this->_disableTexture = disableTexture;
    this->_touchedTexture = touchedTexture;
    this->_containLayer = containLayer;
    this->_mPosition = position;
    this->_id = ID;
    init();
}

bool GameplayButton::init()
{
    UIObject::init();
    _currentSprite = CCSprite::create("1.png");
    _currentSprite->setTexture(this->_enableTexture);
    _currentSprite->setPosition(this->_mPosition);    
    return true;
}

void GameplayButton::update(float dt)
{
    UIObject::update(dt);
}

void GameplayButton::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
    if(CheckTouch(pTouches)){
        changeState(TOUCHED);
        if(_mTouchEventHandler != NULL && _mState == TOUCHED)
        {
            _mTouchEventHandler->touchBegan(this,pTouches, event);
        }
    }
}
void GameplayButton::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
    UIState oldSstate = this->_mState;
    if(CheckTouch(pTouches) == true){
        changeState(TOUCHED);
        if(_mTouchEventHandler != NULL && oldSstate == ENABLE && this->_mState == TOUCHED)
        {
            _mTouchEventHandler->touchBegan(this,pTouches, event);
        }
    } else {
        changeState(ENABLE);
        if(_mTouchEventHandler != NULL && oldSstate == TOUCHED && this->_mState == ENABLE)
        {
            _mTouchEventHandler->touchEnded(this,pTouches, event);
        }
    }
}
void GameplayButton::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
//    UIState oldSstate = this->_mState;
//    changeState(ENABLE);
//    if(_mTouchEventHandler != NULL && oldSstate == TOUCHED)
//    {
//        _mTouchEventHandler->touchEnded(this,pTouches, event);
//    }
    
    UIState oldSstate = this->_mState;
    if(CheckTouch(pTouches) == false){
//        changeState(TOUCHED);
//        if(_mTouchEventHandler != NULL && oldSstate == ENABLE && this->_mState == TOUCHED)
//        {
//            _mTouchEventHandler->touchBegan(this,pTouches, event);
//        }
    } else {
        changeState(ENABLE);
        if(_mTouchEventHandler != NULL && oldSstate == TOUCHED && this->_mState == ENABLE)
        {
            _mTouchEventHandler->touchEnded(this,pTouches, event);
        }
    }

}
void GameplayButton::changeState(UIState state)
{
    _mState = state;
    if(this->_currentSprite != NULL){
        if(this->_mState == TOUCHED){
            this->_currentSprite->setTexture(_touchedTexture);
        } else if(this->_mState == ENABLE){
            this->_currentSprite->setTexture(_enableTexture);
        } else if(this->_mState == DISABLE){
            this->_currentSprite->setTexture(_disableTexture);
        }
    }
}

void GameplayButton::changePosition(cocos2d::CCPoint position){
    this->_mPosition = position;
    if(this->_currentSprite != NULL){
        this->_currentSprite->setPosition(position);
    }
}

bool GameplayButton::CheckTouch(CCSet* pTouches)
{
    if(_mState == ENABLE || _mState == TOUCHED){
        CCSetIterator i;
        CCTouch* touch;
        for( i = pTouches->begin(); i != pTouches->end(); i++) {
            touch = (CCTouch*) (*i);
            if(touch && this->_currentSprite!= NULL && this->_currentSprite->boundingBox().containsPoint(touch->getLocation())) {
                return true;
            }
        }
    }
    return false;
}

CCRect GameplayButton::boundingBox(){
    return this->_currentSprite->boundingBox();
}

void GameplayButton::attach(){
    this->_containLayer->addChild(this->_currentSprite);
}

void GameplayButton::detach(){
    this->_containLayer->removeChild(this->_currentSprite);
}