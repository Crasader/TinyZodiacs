//
//  MultitouchTouchGroup.h
//  HelloWorld
//
//  Created by NhutVM on 5/27/14.
//
//

#ifndef __HelloWorld__MultitouchTouchGroup__
#define __HelloWorld__MultitouchTouchGroup__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class MultitouchTouchGroup: public cocos2d::gui::TouchGroup
{
private:
protected:
//    virtual void assignHoldWidget(cocos2d::gui::Widget* widget);
    
    CCArray* listAssignedWidget;
public:
    MultitouchTouchGroup();
    ~MultitouchTouchGroup();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void onEnter();
    
    virtual bool init();
    
    bool checkEventWidget(CCTouch* touch, CCEvent *pEvent);
    
    bool checkTouchEvent(cocos2d::gui::Widget *root, CCTouch* touch, CCEvent* pEvent);
};


#endif /* defined(__HelloWorld__MultitouchTouchGroup__) */
