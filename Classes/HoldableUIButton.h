//
//  HoldableUIButton.h
//  HelloWorld
//
//  Created by NhutVM on 5/28/14.
//
//

#ifndef __HelloWorld__HoldableUIButton__
#define __HelloWorld__HoldableUIButton__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"

USING_NS_CC;
class HoldableUIButton : public cocos2d::gui::UIButton
{
private:
protected:
public:
    CCArray* listTouchedPoint;
    
    HoldableUIButton();
    ~HoldableUIButton();
    
    bool init();
    void copy(cocos2d::gui::Button* button);
    
    void update(float dt);
    
    static HoldableUIButton* create();
    
    virtual bool onTouchBegan(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchMoved(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchEnded(CCTouch *touch, CCEvent *unused_event);
    virtual void onTouchCancelled(CCTouch *touch, CCEvent *unused_event);
    
    void loadTextures(const char* normal,const char* selected,const char* disabled,cocos2d::gui::TextureResType texType);
    CC_SYNTHESIZE_READONLY(bool, isActive, Active);
    void setActive(bool value);
};

#endif /* defined(__HelloWorld__HoldableUIButton__) */
