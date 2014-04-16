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



class GameMenuLayer: public cocos2d::CCLayer, public iUIObjectTouchEventInterface
{
public:
    CCLabelTTF* label;
    
    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(GameMenuLayer);
    
    void LeftCallBack(cocos2d::CCObject* sender);
    void RightCallBack(cocos2d::CCObject* sender);
    void UpCallBack(cocos2d::CCObject* sender);
    void DownCallBack(cocos2d::CCObject* sender);

    


    virtual void touchBegan(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchHold(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchEnded(void* sender ,CCSet* pTouches, CCEvent* event);
    
private:
    
    
};

#endif /* defined(__SampleCocosProject__GameMenuLayer__) */
