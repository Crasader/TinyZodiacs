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
    this->listAssignedWidget = CCArray::create();
    this->listAssignedWidget->retain();
}

MultitouchTouchGroup::~MultitouchTouchGroup()
{
    this->listAssignedWidget->removeAllObjects();
    this->listAssignedWidget->release();
}

// default implements are used to call script callback if exist

void MultitouchTouchGroup::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator i;
    CCTouch* mTouch;
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
        mTouch = (CCTouch*) (*i);
        ccTouchBegan(mTouch, pEvent);
    }
    //    CCTouch *mTouch = (CCTouch *)pTouches->anyObject();
    //    CCLOG("ccTouchesBegan %d",pTouches->count());
}

void MultitouchTouchGroup::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator i;
    CCTouch* mTouch;
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
        mTouch = (CCTouch*) (*i);
        ccTouchMoved(mTouch, pEvent);
    }
    
}

void MultitouchTouchGroup::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator i;
    CCTouch* mTouch;
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
        mTouch = (CCTouch*) (*i);
        ccTouchEnded(mTouch, pEvent);
    }
    
}

void MultitouchTouchGroup::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator i;
    CCTouch* mTouch;
    for( i = pTouches->begin(); i != pTouches->end(); i++) {
        mTouch = (CCTouch*) (*i);
        ccTouchCancelled(mTouch, pEvent);
    }

}

void MultitouchTouchGroup::onEnter()
{
    setTouchMode(kCCTouchesAllAtOnce);
    setTouchEnabled(true);
    CCLayer::onEnter();
}

bool MultitouchTouchGroup::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return checkEventWidget(pTouch, pEvent);
}

void MultitouchTouchGroup::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCArray* removeArr = CCArray::create();
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(selectedWidgetArray->arr[i]);
        hitWidget->onTouchMoved(pTouch, pEvent);
    }
    
    CCObject* object = NULL;
    cocos2d::gui::Widget* swidget = NULL;
    CCARRAY_FOREACH(this->listAssignedWidget, object)
    {
        cocos2d::gui::Widget* widget = static_cast<cocos2d::gui::Widget*>(object);
        if(widget->hitTest(pTouch->getLocation()) == true)
        {
            if(widget->hitTest(pTouch->getPreviousLocation()) == false)
            {
                ccTouchBegan(pTouch, pEvent);
                swidget = widget;
                break;
            }
        }
    }
    if(swidget)
    {
        CCObject* object1 = NULL;
        CCARRAY_FOREACH(this->listAssignedWidget, object1)
        {
            cocos2d::gui::Widget* widget2 = static_cast<cocos2d::gui::Widget*>(object1);
            if(widget2 != swidget)
            {
                removeArr->addObject(widget2);
            }
        }
    }
    
    CCARRAY_FOREACH(removeArr, object)
    {
        cocos2d::gui::Widget* widget2 = static_cast<cocos2d::gui::Widget*>(object);
        m_pSelectedWidgets->removeObject(object);
        widget2->onTouchEnded(pTouch, pEvent);
    }
}

void MultitouchTouchGroup::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCArray* removeArr = CCArray::create();
    ccArray* selectedWidgetArray = m_pSelectedWidgets->data;
    int length = selectedWidgetArray->num;
    for (int i=0; i<length; ++i)
    {
        
        bool aaa = false;
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(selectedWidgetArray->arr[i]);
        if(hitWidget->hitTest(pTouch->getLocation()) || hitWidget->hitTest(pTouch->getStartLocation()))
        {
            removeArr->addObject(hitWidget);
            aaa = true;
        }
        if(aaa == false)
        {
            HoldableButton* holdableButton = dynamic_cast<HoldableButton*>(hitWidget);
            if(holdableButton)
            {
                if(holdableButton->idTouch == pTouch->getID())
                {
                    removeArr->addObject(hitWidget);
                }
            }
        }
    }
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(removeArr, object)
    {
        cocos2d::gui::Widget* hitWidget = (cocos2d::gui::Widget*)(object);
        this->m_pSelectedWidgets->removeObject(hitWidget);
        hitWidget->onTouchEnded(pTouch, pEvent);
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
    //
    CCObject* hitWidget;
    CCARRAY_FOREACH(this->listAssignedWidget, hitWidget)
    {
        //        if(((cocos2d::gui::Widget*)hitWidget)->hitTest(pTouch->getLocation()) && ((cocos2d::gui::Widget*)hitWidget)->isFocused())
        {
            ((cocos2d::gui::Widget*)hitWidget)->onTouchCancelled(pTouch, pEvent);
        }
    }
}

bool MultitouchTouchGroup::init()
{
    if(!TouchGroup::init())
    {
        return false;
    }
    this->setTouchEnabled(true);
 
    return true;
}

bool MultitouchTouchGroup::checkEventWidget(CCTouch* touch, CCEvent *pEvent)
{
    checkTouchEvent(m_pRootWidget,touch, pEvent);
    
    return (m_pSelectedWidgets->count() > 0);
}

bool MultitouchTouchGroup::checkTouchEvent(cocos2d::gui::Widget *root, CCTouch* touch, CCEvent* pEvent)
{
    return TouchGroup::checkTouchEvent(root, touch, pEvent);
}