//
//  UIObject.cpp
//  CharacterDemo
//
//  Created by Nhut on 3/20/14.
//
//

#include "UIObject.h"

bool UIObject::init()
{
    this->_mState = ENABLE;
    return true;
}



void UIObject::update(float dt)
{
    if(_mState == TOUCHED && _mTouchEventHandler != NULL)
    {
        _mTouchEventHandler->touchHold(this,NULL, NULL);
    }
}

void UIObject::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
    if(_mState == ENABLE){
        _mTouchEventHandler->touchBegan(this,pTouches, event);
    }
}
void UIObject::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
    
}
void UIObject::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
    if(_mState == ENABLE){
        _mTouchEventHandler->touchEnded(this,pTouches, event);
    }
}

void UIObject::changeState(UIState state)
{
    _mState = state;
}

void UIObject::changePosition(cocos2d::CCPoint position){
    this->_mPosition = position;
}

void UIObject::attach(){
    
}

void UIObject::detach(){
    
}

bool UIObject::CheckTouch(CCSet* pTouches){
    return false;
}