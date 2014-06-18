//
//  PauseLayer.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/18/14.
//
//

#ifndef __TinyZodiacs__PauseLayer__
#define __TinyZodiacs__PauseLayer__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"

USING_NS_CC;
class PauseLayer: public cocos2d::gui::TouchGroup
{
private:
    
protected:
    void loadAllUI(cocos2d::gui::Widget* ul);
    void playInAnimation();
    void playOutAnimation(bool shouldQuit);
    void detachFromParent();
    void detachFromParentAndQuit();
public:
    cocos2d::gui::Button *btnQuit, *btnResume;
    cocos2d::gui::UIPanel  *mainPanel;
    PauseLayer();
    ~PauseLayer();
    
    bool init();
    
    void resumeButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void quitButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    
    CREATE_FUNC(PauseLayer);
};
#endif /* defined(__TinyZodiacs__PauseLayer__) */
