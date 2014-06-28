//
//  HoldableButton.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/27/14.
//
//

#include "HoldableButton.h"

HoldableButton::HoldableButton()
{
    this->isHolding = false;
}

HoldableButton::~HoldableButton()
{
    
}

bool HoldableButton::init()
{
    if(!Button::init())
    {
        return false;
    }
    this->scheduleUpdate();
    return true;
}

void HoldableButton::update(float dt)
{
    if(this->isHolding)
    {
        if (_touchEventListener && _touchEventSelector)
        {
            (_touchEventListener->*_touchEventSelector)(this,cocos2d::gui::TOUCH_EVENT_HOLD);
        }
    }
}

void HoldableButton::copy(cocos2d::gui::Button* button)
{
    this->copyProperties(button);
    this->copySpecialProperties(button);
}

bool HoldableButton::onTouchBegan(CCTouch *touch, CCEvent *unused_event)
{
    if(Button::onTouchBegan(touch, unused_event))
    {
        this->isHolding = true;
        this->idTouch = touch->getID();
        return true;
    }
    
    return false;
}

void HoldableButton::onTouchMoved(CCTouch *touch, CCEvent *unused_event)
{
    _touchMovePos = touch->getLocation();
    // setFocused();
    Widget* widgetParent = getWidgetParent();
    if (widgetParent)
    {
        widgetParent->checkChildInfo(1,this,_touchMovePos);
    }
    moveEvent();
}

void HoldableButton::onTouchEnded(CCTouch *touch, CCEvent *unused_event)
{
    if((this->_touchMovePos.x == touch->getLocation().x && this->_touchMovePos.y == touch->getLocation().y ) || hitTest(touch->getLocation()))
    {
         Button::onTouchEnded(touch, unused_event);
    }
    this->isHolding = false;
    Button::onTouchEnded(touch, unused_event);
}

void HoldableButton::onTouchCancelled(CCTouch *touch, CCEvent *unused_event)
{
    Button::onTouchCancelled(touch, unused_event);
}