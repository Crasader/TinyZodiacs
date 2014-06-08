//
//  HoldableUIButton.cpp
//  HelloWorld
//
//  Created by NhutVM on 5/28/14.
//
//

#include "HoldableUIButton.h"
HoldableUIButton::HoldableUIButton()
{
    this->isActive = true;
}

HoldableUIButton::~HoldableUIButton()
{
//    this->listTouchedPoint->removeAllObjects();
//    this->listTouchedPoint->release();
}

HoldableUIButton* HoldableUIButton::create()
{
    HoldableUIButton* widget = new HoldableUIButton();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool HoldableUIButton::init()
{
    if(!cocos2d::gui::Button::init())
    {
        return false;
    }
    this->scheduleUpdate();
    
//    this->listTouchedPoint = CCArray::create();
//    this->listTouchedPoint->retain();
    return true;
}

void HoldableUIButton::copy(cocos2d::gui::Button* button)
{
    this->copyProperties(button);
    this->copySpecialProperties(button);
}

void HoldableUIButton::update(float dt)
{
    if(this->isActive)
    {
        if(this->isFocused())
        {
            if (_touchEventListener && _touchEventSelector)
            {
                (_touchEventListener->*_touchEventSelector)(this,cocos2d::gui::TOUCH_EVENT_HOLD);
            }
        }
    }
    else
    {
        if(!this->isFocused())
        {
            this->setBright(false);
        }
        else
        {
            this->setFocused(false);
        }
    }
//    CCLOG("update %s - %d",this->getName(),this->listTouchedPoint->count());
}

bool HoldableUIButton::onTouchBegan(CCTouch *touch, CCEvent *unused_event)
{
    if(isActive)
    {
        return cocos2d::gui::Button::onTouchBegan(touch,unused_event);
    }
    else
    {
        _hitted = false;
        if (isEnabled() && isTouchEnabled())
        {
            _touchStartPos = touch->getLocation();
            if(hitTest(_touchStartPos) && clippingParentAreaContainPoint(_touchStartPos))
            {
                _hitted = true;
            }
        }
        if (!_hitted)
        {
            return false;
        }
        setFocused(true);
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            widgetParent->checkChildInfo(0,this,_touchStartPos);
        }
//        pushDownEvent();
        return !_touchPassedEnabled;
    }
    return false;
}

void HoldableUIButton::onTouchMoved(CCTouch *touch, CCEvent *unused_event)
{
    if(isActive)
    {
        _touchMovePos = touch->getLocation();
//        setFocused(hitTest(_touchMovePos));
        Widget* widgetParent = getWidgetParent();
        if (widgetParent)
        {
            widgetParent->checkChildInfo(1,this,_touchMovePos);
        }
//        moveEvent();
        
        if(hitTest(touch->getLocation()) == true)
        {
            if(hitTest(touch->getPreviousLocation()) == false)
            {
                this->onTouchBegan(touch, unused_event);
            }
        }
        else
        {
            if(hitTest(touch->getPreviousLocation()) == true)
            {
                //cocos2d::gui::UIButton::onTouchEnded(touch,unused_event);
                this->onTouchEnded(touch, unused_event);
            }
        }
    }
}

void HoldableUIButton::onTouchEnded(CCTouch *touch, CCEvent *unused_event)
{
 if(isActive)
    {
        cocos2d::gui::Button::onTouchEnded(touch,unused_event);
    }
}

void HoldableUIButton::onTouchCancelled(CCTouch *touch, CCEvent *unused_event)
{
    if(isActive)
    {
        cocos2d::gui::Button::onTouchCancelled(touch,unused_event);
    }
}

void HoldableUIButton::loadTextures(const char* normal,const char* selected,const char* disabled,cocos2d::gui::TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void HoldableUIButton::setActive(bool value)
{
    this->isActive = value;
    if(this->isActive)
    {
        this->setBright(true);
    }
    else
    {
        this->setBright(false);
    }
}