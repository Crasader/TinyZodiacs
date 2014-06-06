//
//  MainMenuLayer.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/5/14.
//
//

#ifndef __TinyZodiacs__MainMenuLayer__
#define __TinyZodiacs__MainMenuLayer__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"

USING_NS_CC;
class MainMenuLayer: public cocos2d::gui::TouchGroup
{
private:
protected:
    void loadAllUI(cocos2d::gui::Widget* ul);
public:
    cocos2d::gui::Button *btnPlay, *btnInfo, *btnOption;
    cocos2d::gui::ImageView *backgroundLayer;
    
    MainMenuLayer();
    
    ~MainMenuLayer();
    
    bool init();
    
    static CCScene* scene();
    static MainMenuLayer* layer();
    
    void playButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void infoButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void optionButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);

    
    CREATE_FUNC(MainMenuLayer);
};


#endif /* defined(__TinyZodiacs__MainMenuLayer__) */
