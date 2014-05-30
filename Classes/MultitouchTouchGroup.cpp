//
//  MultitouchTouchGroup.cpp
//  HelloWorld
//
//  Created by NhutVM on 5/27/14.
//
//

#include "MultitouchTouchGroup.h"

#include "AbstractScene.h"

MultitouchTouchGroup::MultitouchTouchGroup()
{

}

MultitouchTouchGroup::~MultitouchTouchGroup()
{
    this->listAssignedWidget->removeAllObjects();
    this->listAssignedWidget->release();
}

// default implements are used to call script callback if exist

void MultitouchTouchGroup::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *mTouch = (CCTouch *)pTouches->anyObject();
    ccTouchBegan(mTouch, pEvent);
//    CCLOG("ccTouchesBegan %d",pTouches->count());
}

void MultitouchTouchGroup::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *mTouch = (CCTouch *)pTouches->anyObject();
    ccTouchMoved(mTouch, pEvent);
//    CCLOG("ccTouchesMoved %d",pTouches->count());
}

void MultitouchTouchGroup::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *mTouch = (CCTouch *)pTouches->anyObject();
    ccTouchEnded(mTouch, pEvent);
//    CCLOG("ccTouchesEnded %d",pTouches->count());
}

void MultitouchTouchGroup::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *mTouch = (CCTouch *)pTouches->anyObject();
    ccTouchCancelled(mTouch, pEvent);
//    CCLOG("ccTouchesCancelled %d",pTouches->count());
}

void MultitouchTouchGroup::onEnter()
{
    setTouchMode(kCCTouchesAllAtOnce);
    setTouchEnabled(true);
    CCLayer::onEnter();
}

bool MultitouchTouchGroup::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("ccTouchBegan");
    return checkEventWidget(pTouch, pEvent);
}

void MultitouchTouchGroup::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("ccTouchMoved");
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(selectedWidgetArray->arr[i]);
        if(this->listAssignedWidget->indexOfObject(hitWidget) == CC_INVALID_INDEX && hitWidget->hitTest(pTouch->getLocation()) == false)
        {
            hitWidget->onTouchMoved(pTouch, pEvent);
        }
    }
    //
    CCObject* widget;
    CCARRAY_FOREACH(this->listAssignedWidget, widget)
    {
        ((cocos2d::gui::Widget*)widget)->onTouchMoved(pTouch, pEvent);
    }
}

void MultitouchTouchGroup::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("ccTouchEnded");
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(selectedWidgetArray->arr[i]);
        if(hitWidget->hitTest(pTouch->getLocation()))
        {
            m_pSelectedWidgets->removeObject(hitWidget);
            hitWidget->onTouchEnded(pTouch, pEvent);
        }
    }
    //
    CCObject* hitWidget;
    CCARRAY_FOREACH(this->listAssignedWidget, hitWidget)
    {
//        if(((cocos2d::gui::Widget*)hitWidget)->hitTest(pTouch->getLocation()) && ((cocos2d::gui::Widget*)hitWidget)->isFocused())
        {
            ((cocos2d::gui::Widget*)hitWidget)->onTouchEnded(pTouch, pEvent);
        }
    }
    
}

void MultitouchTouchGroup::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(selectedWidgetArray->arr[0]);
        m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchCancelled(pTouch, pEvent);
    }
}

bool MultitouchTouchGroup::init()
{
    if(!TouchGroup::init())
    {
        return false;
    }
    this->setTouchEnabled(true);
    
    this->listAssignedWidget = CCArray::create();
    this->listAssignedWidget->retain();
    return true;
}