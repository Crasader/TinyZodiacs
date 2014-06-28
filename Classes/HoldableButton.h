//
//  HoldableButton.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/27/14.
//
//

#ifndef __TinyZodiacs__HoldableButton__
#define __TinyZodiacs__HoldableButton__

#include <iostream>

class HoldableButton;

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;

class HoldableButton : public cocos2d::gui::Button
{
private:
    CCPoint lastPositionMove;
    bool isHolding;
protected:
public:
    int idTouch;
    HoldableButton();
    ~HoldableButton();
    
    virtual bool init();
    
    void copy(cocos2d::gui::Button* button);
    
    void update(float dt);
    
    virtual bool onTouchBegan(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchMoved(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchEnded(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchCancelled(CCTouch *touch, CCEvent *unused_event);

    
    CREATE_FUNC(HoldableButton);
};


#endif /* defined(__TinyZodiacs__HoldableButton__) */
