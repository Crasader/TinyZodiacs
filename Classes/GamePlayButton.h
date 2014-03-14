//
//  GamePlayButton.h
//  CharacterDemo
//
//  Created by Nhut on 3/20/14.
//
//

#ifndef __CharacterDemo__GamePlayButton__
#define __CharacterDemo__GamePlayButton__

#include <iostream>
#include "UIObject.h"
#include "cocos2d.h"

USING_NS_CC;

class GameplayButton: public UIObject
{
private:
    GameplayButton(CCTexture2D * enableTexture, CCTexture2D * disableTexture, CCTexture2D * touchedSprite, CCLayer* containLayer, CCPoint position, std::string ID);
protected:
    virtual bool init();
    virtual bool CheckTouch(CCSet* pTouches);
    
    CCTexture2D * _enableTexture;
    CCTexture2D * _disableTexture;
    CCTexture2D * _touchedTexture;
public:
    CC_SYNTHESIZE(CCSprite*, _currentSprite, CurrentSprite);
    
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    static GameplayButton* create(CCTexture2D * enableTexture, CCTexture2D * disableTexture, CCTexture2D *touchedTexture, CCLayer* containLayer, CCPoint position, std::string ID){
        return new GameplayButton(enableTexture,disableTexture,touchedTexture,containLayer, position, ID);
    };
    
    virtual void update (float dt);
    virtual void changeState(UIState state);
    virtual void changePosition(CCPoint position);
    
    CCRect boundingBox();
    
    void attach();
    void detach();
};


#endif /* defined(__CharacterDemo__GamePlayButton__) */
