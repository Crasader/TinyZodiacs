//
//  GameMenuLayer.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/9/14.
//
//

#ifndef __SampleCocosProject__GameMenuLayer__
#define __SampleCocosProject__GameMenuLayer__

#include <iostream>
#include "cocos2d.h"
#include "iUIObjectTouchInterface.h"
#include "Controller.h"
#include "ControllerLayer.h"



class GameMenuLayer: public cocos2d::CCLayer, public iUIObjectTouchEventInterface, public Controller
{
public:
    CCLabelTTF* label;
     CCLabelTTF* monsterCount;
    ControllerLayer * mlayer;
    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(GameMenuLayer);


    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    


    virtual void touchBegan(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchHold(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchEnded(void* sender ,CCSet* pTouches, CCEvent* event);
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    virtual bool removeSubController(Controller* controller);
    
private:
    
    
};

#endif /* defined(__SampleCocosProject__GameMenuLayer__) */
