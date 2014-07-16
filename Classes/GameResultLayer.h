//
//  GameResultLayer.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/16/14.
//
//

#ifndef __TinyZodiacs__GameResultLayer__
#define __TinyZodiacs__GameResultLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Achievement.h"

USING_NS_CC;


class GameResultLayer: public cocos2d::gui::TouchGroup
{
private:
    
protected:
    void loadAllUI(cocos2d::gui::Widget* ul);
    void playInAnimation();
    void playOutAnimation(bool shouldQuit);
    void detachFromParent();
    void detachFromParentAndQuit();
public:
    cocos2d::gui::Button *btnQuit;
    cocos2d::gui::Button *btnRestart;
    cocos2d::gui::UIPanel *mainPanel;
    cocos2d::gui::Label* lblTime;
    cocos2d::gui::Label* lblHightScore;
    cocos2d::gui::Label* lblScore;
    cocos2d::gui::Label* lblMoneyLeft;
    
    GameResultLayer();
    ~GameResultLayer();
    
    bool init();
    
    void restartButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void quitButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    
    void setTime(int time);
    void setHightScore(int score);
    void setScore(int score);
    void setResult(bool win, Achievement* achievement);
    void loadUIWin();
    void loadUILose();
    
    CREATE_FUNC(GameResultLayer);
};


#endif /* defined(__TinyZodiacs__GameResultLayer__) */
