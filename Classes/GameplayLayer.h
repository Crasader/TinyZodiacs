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
#include "AbstractScene.h"
#include "cocos2d.h"
#include "CocosGUI.h"
#include "HoldableUIButton.h"
#include "Controller.h"
#include "EffectManager.h"
#include "TextShowEffect.h"

USING_NS_CC;

class GameplayLayer: public AbstractScene, public Controller
{
private:
    void cloneAndRemoveButton(cocos2d::gui::Widget* ul, HoldableUIButton* mButton,cocos2d::gui::Button* button);
protected:
    cocos2d::gui::LoadingBar *processMonsterLeft;
    cocos2d::gui::LabelBMFont *lblWave, *lblTimeLeft, *lblMoney, *lblMonsterLeft;
    cocos2d::gui::ListView *listWave;
    
    void loadAllUI(cocos2d::gui::Widget* ul);
public:
    HoldableUIButton *btnLeft, *btnRight, *btnJump, *btnSkill0, *btnSkill1, *btnSkill2;
    
    GameplayLayer();
    
    ~GameplayLayer();
    
    bool init();
    
    static CCScene* scene();
    static GameplayLayer* layer();
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    CREATE_FUNC(GameplayLayer);
    
    void setGoldValue(int number);
    void setTimeValue(int number);
    void setWaveValue(int number);
    void setMonsterProcessValue(int maxMonsterQuantity, int currentMonsterQuantity);
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    virtual bool removeSubController(Controller* controller);
    
    void leftButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void rightButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void jumpButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill0ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill1ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void skill2ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);

};

#endif /* defined(__HelloWorld__GameplayScene__) */
