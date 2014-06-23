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
#include "cocos-ext.h"

USING_NS_CC;
class MainMenuLayer: public cocos2d::gui::TouchGroup
{
private:
    float soundBtnScale, musicButtonScale, fbBtnScale, gpBtnScale;
    CCPoint soundBtnPosition, musicButtonPosition, fbBtnPosition, gpBtnPosition;
    
    bool isOPtionShown, isInforShown;
protected:
    void loadAllUI(cocos2d::gui::Widget* ul);
    
    CCAction* initButtonAnimation(cocos2d::gui::Widget* target, cocos2d::gui::Widget* parent, CCPoint originalPosition, float originalScale, bool isIn);
    
    void playOptionItemAnimation(CCNode* sender, void* data);
    void setOptionPanelVisibilityValue();
    
    void playInforItemAnimation(CCNode* sender, void* data);
    void setInforPanelVisibilityValue();
public:
    cocos2d::gui::Button *btnPlay, *btnInfo, *btnOption, *btnMusic, *btnSound, *btnGooglePlus, *btnFacebook;
    cocos2d::gui::ImageView *backgroundLayer;
    cocos2d::gui::UIPanel  *optionPanel, *inforPanel;
    MainMenuLayer();
    ~MainMenuLayer();
    
    bool init();
    
    void playButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void infoButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void optionButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void soundButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void musicButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void facebookButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void googleplusButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);

    
    CREATE_FUNC(MainMenuLayer);
};


#endif /* defined(__TinyZodiacs__MainMenuLayer__) */
