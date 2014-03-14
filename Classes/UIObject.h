//
//  UIObject.h
//  CharacterDemo
//
//  Created by Nhut on 3/20/14.
//
//

#ifndef __CharacterDemo__UIObject__
#define __CharacterDemo__UIObject__

#include <iostream>
#include "cocos2d.h"
#include "iUIObjectTouchInterface.h"

USING_NS_CC;

enum UIState {ENABLE, DISABLE, TOUCHED};


class UIObject
{
private:
    
protected:
    virtual bool init();
    
    bool CheckTouch(CCSet* pTouches);
public:
    CC_SYNTHESIZE(std::string, _id, ID);
    //
    CC_SYNTHESIZE_READONLY(UIState, _mState, State);
    CC_SYNTHESIZE_READONLY(CCPoint, _mPosition, Position);
    //
    CC_SYNTHESIZE(iUIObjectTouchEventInterface *, _mTouchEventHandler, TouchEventHandler);
    CC_SYNTHESIZE_READONLY(CCLayer*, _containLayer, ContainLayer);
    CC_SYNTHESIZE_READONLY(CCArray*, _mListTouchedPoint, ListTouchedPoint);

    //THE OVERRIDES
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    void update (float dt);
    void changeState(UIState state);
    void changePosition(CCPoint position);

    void attach();
    void detach();
};

#endif /* defined(__CharacterDemo__UIObject__) */
