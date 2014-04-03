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
#include "Constants.h"

USING_NS_CC;

class GameplayButton: public UIObject
{
private:
    GameplayButton(CCSpriteFrame * enableTexture, CCSpriteFrame * disableTexture, CCSpriteFrame * touchedSprite, CCLayer* containLayer, CCPoint position, std::string ID);
protected:
    virtual bool init();
    virtual bool CheckTouch(CCSet* pTouches);
    
    CCSpriteFrame * _enableTexture;
    CCSpriteFrame * _disableTexture;
    CCSpriteFrame * _touchedTexture;
public:
    CC_SYNTHESIZE(CCSprite*, _currentSprite, CurrentSprite);
    
    virtual void setTextureSelector(TextureSelector selector);
    
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    
    static GameplayButton* create(CCSpriteFrame * enableTexture, CCSpriteFrame * disableTexture, CCSpriteFrame *touchedTexture, CCLayer* containLayer, CCPoint position, std::string ID){
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
