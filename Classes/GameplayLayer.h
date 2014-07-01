//
//  GameplayScene.h
//  HelloWorld
//
//  Created by Minh Nhut Vo on 5/26/14.
//
//

#ifndef __HelloWorld__GameplayScene__
#define __HelloWorld__GameplayScene__

class GameplayLayer;

#include <iostream>
#include "cocos-ext.h"
#include "AbstractScene.h"
#include "cocos2d.h"
#include "HoldableUIButton.h"
#include "HoldableButton.h"
#include "Controller.h"
#include "EffectManager.h"
#include "TextShowEffect.h"
#include "XMLButtonSelectorParser.h"

USING_NS_CC;

class GameplayLayer: public AbstractScene, public Controller
{
private:
    CCArray* defenseList;
    void cloneAndRemoveButton(cocos2d::gui::Widget* ul, HoldableButton* mButton,cocos2d::gui::Button* button);
    
    CCPoint correctPositionDefenseListGroup;
    cocos2d::gui::Widget* mainLayout;
    cocos2d::gui::Button* btnOpenDefenseList;
    cocos2d::gui::Button* btnCloseDefenseList;
protected:
    cocos2d::gui::LabelBMFont *lblWave, *lblTimeLeft, *lblMoney, *lblMonsterLeft;
    cocos2d::gui::ListView* lvDefense;
    cocos2d::gui::Layout* defenseListGroup;
    cocos2d::gui::Layout* actionControlPanel;
    cocos2d::gui::Layout* movingControlPanel;
    cocos2d::gui::ImageView* resultImage;
    cocos2d::gui::UIButton* btnPause;
    
    void loadAllUI(cocos2d::gui::Widget* ul);
    void initUI();
public:
    HoldableButton *btnLeft, *btnRight, *btnJump, *btnSkill0, *btnSkill1, *btnSkill2;
    GameplayLayer();
    
    ~GameplayLayer();
    
    bool init();
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    CREATE_FUNC(GameplayLayer);
    
    void setGoldValue(int number);
    void setTimeValue(int number);
    void setWaveValue(const char* waveName);
    void setMonsterProcessValue(int maxMonsterQuantity, int currentMonsterQuantity);
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    virtual bool removeSubController(Controller* controller);
    
    void leftButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void rightButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void jumpButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill0ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill1ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill2ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void openDefenseListButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void closeDefenseListButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void pauseButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    
    void openDefenseListView(bool open);
    
    void activeDefenseList();
    void deactiveDefenseList();
    void activeActionControl();
    void deactiveActionControl();
    void activeMovingControl();
    void deactiveMovingControl();
    
    void openActionControlPanel();
    void closeActionControlPanel();
    void openMovingControlPanel();
    void closeMovingControlPanel();
    void openDefenseListGroup();
    void closeDefenseListGroup();
    void finishAnimationOfActionControl();
    void finishAnimationOfDefenseListGroup();
    void setEnableWidgetInDefenseListGroup(bool able);
    void setEnableWidgetInActionControl(bool able);
    void setEnableWidgetInMovingControl(bool able);
    void setButtonDisable(cocos2d::gui::Button* button, bool disable);
    
    void loadDefenseList();
    void refeshDefenseListView(int cost);
    void setDisableUI(bool disable);
    
    void listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    
};

#endif /* defined(__HelloWorld__GameplayScene__) */
