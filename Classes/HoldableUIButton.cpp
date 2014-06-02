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
    this->listTouchedPoint->removeAllObjects();
    this->listTouchedPoint->release();
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
    if(!cocos2d::gui::UIButton::init())
    {
        return false;
    }
    this->scheduleUpdate();
    
    this->listTouchedPoint = CCArray::create();
    this->listTouchedPoint->retain();
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
    CCLOG("%s - %d",this->getName(),this->listTouchedPoint->count());
}

bool HoldableUIButton::onTouchBegan(CCTouch *touch, CCEvent *unused_event)
{
    if(isActive)
    {
        if(this->listTouchedPoint->indexOfObject(touch) == CC_INVALID_INDEX && hitTest(touch->getLocation()))
        {
            listTouchedPoint->addObject(touch);
        }
        return cocos2d::gui::UIButton::onTouchBegan(touch,unused_event);
    }
    return false;
}

void HoldableUIButton::onTouchMoved(CCTouch *touch, CCEvent *unused_event)
{
    if(isActive)
    {
        if(this->listTouchedPoint->indexOfObject(touch) != CC_INVALID_INDEX && !hitTest(touch->getLocation()))
        {
//            this->onTouchEnded(touch, unused_event);
            listTouchedPoint->removeObject(touch);
            cocos2d::gui::UIButton::onTouchEnded(touch,unused_event);
        }
        else if(this->listTouchedPoint->indexOfObject(touch) == CC_INVALID_INDEX && hitTest(touch->getLocation()))
        {
            this->onTouchBegan(touch, unused_event);
        }
    }
    else
    {
        listTouchedPoint->removeObject(touch);
    }
    //cocos2d::gui::UIButton::onTouchMoved(touch,unused_event);
}

void HoldableUIButton::onTouchEnded(CCTouch *touch, CCEvent *unused_event)
{
//    if(hitTest(touch->getLocation()))
    {
        listTouchedPoint->removeObject(touch);
    }
    if(isActive && ((hitTest(touch->getLocation()) && this->isFocused()) || (this->listTouchedPoint->indexOfObject(touch) != CC_INVALID_INDEX && !hitTest(touch->getLocation()))))
    {
        cocos2d::gui::UIButton::onTouchEnded(touch,unused_event);
    }
}

void HoldableUIButton::onTouchCancelled(CCTouch *touch, CCEvent *unused_event)
{
//    if(hitTest(touch->getLocation()))
    {
        listTouchedPoint->removeObject(touch);
    }
    if(isActive)
    {
        cocos2d::gui::UIButton::onTouchCancelled(touch,unused_event);
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