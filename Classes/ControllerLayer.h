//
//  ControllerLayer.h
//  CharacterDemo
//
//  Created by Nhut on 3/16/14.
//
//

#ifndef __CharacterDemo__ControllerLayer__
#define __CharacterDemo__ControllerLayer__

#include <iostream>
#include "cocos2d.h"
#include "iUIObjectTouchInterface.h"
#include "GamePlayButton.h"
#include "UIConstant.h"

USING_NS_CC;
class ControllerLayer: public cocos2d::CCLayer
{
private:
    bool isJumpButtonTouched;
    bool isLeftButtonTouched;
    bool isRightButtonTouched;

    
    char * LEFT_BTN_SPRITE ;
    char * RIGHT_BTN_SPRITE ;
    char * JUMP_BTN_SPRITE ;
    
//    GameplayButton * _LeftButtonSprite;
//    GameplayButton * _RightButtonSprite;
//    GameplayButton * _JumpButtonSprite;
//    GameplayButton * _AtkButtonSprite;
//    GameplayButton * _Skill1ButtonSprite;
//    GameplayButton * _Skill2ButtonSprite;


    
    CCLayer * _ContainerLayer;
    
    //
    virtual bool init();
    //
    CREATE_FUNC(ControllerLayer);
    
    //function
    ButtonType checkTouch(CCTouch * touch);
    
    iUIObjectTouchEventInterface * _LeftButtonEventHandler;
    iUIObjectTouchEventInterface * _RightButtonEventHandler;
    iUIObjectTouchEventInterface * _JumpButtonEventHandler;
    iUIObjectTouchEventInterface * _AtkButtonEventHandler;

public:
    CC_SYNTHESIZE(GameplayButton *, _LeftButtonSprite, LeftButtonSprite);
    CC_SYNTHESIZE(GameplayButton *, _RightButtonSprite, RightButtonSprite);
    CC_SYNTHESIZE(GameplayButton *, _JumpButtonSprite, JumpButtonSprite);
    CC_SYNTHESIZE(GameplayButton *, _AtkButtonSprite, AtkButtonSprite);
    CC_SYNTHESIZE(GameplayButton *, _Skill1ButtonSprite, Skill1ButtonSprite);
    CC_SYNTHESIZE(GameplayButton *, _Skill2ButtonSprite, Skill2ButtonSprite);

    //Get, set declare
    void setLeftButtonEventHadler(iUIObjectTouchEventInterface * handler);
    
    void setRightButtonEventHadler(iUIObjectTouchEventInterface * handler);

    void setJumpButtonEventHadler(iUIObjectTouchEventInterface * handler);

    void setAtkButtonEventHadler(iUIObjectTouchEventInterface * handler);
    
    void setSkill1ButtonEventHadler(iUIObjectTouchEventInterface * handler);

    void setSkill2ButtonEventHadler(iUIObjectTouchEventInterface * handler);
    //Fuctions
    ~ControllerLayer();
    
    static ControllerLayer * create(cocos2d::CCLayer * containLayer);
    
    static ControllerLayer * getInstance();
    
    void setLeftButtonPosition(float x, float y);
    void setRightButtonPosition(float x, float y);
    void setJumpButtonPosition(float x, float y);
    void setAtkButtonPosition(float x, float y);
    void setSkill1ButtonPosition(float x, float y);
    void setSkill2ButtonPosition(float x, float y);


    //THE OVERRIDES
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    void update (float dt);
};

#endif /* defined(__CharacterDemo__ControllerLayer__) */
