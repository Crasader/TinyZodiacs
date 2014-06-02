//
//  GameObjectLayer.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/9/14.
//
//

#ifndef __SampleCocosProject__GameObjectLayer__
#define __SampleCocosProject__GameObjectLayer__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Character.h"
#include "GameWorld.h"
#include "CharacterActionEngine.h"
#include "ControllerManager.h"
#include "Controller.h"


class GameObjectLayer: public cocos2d::CCLayer, public Controller
{
public:
    CCNode* node;
    GameObjectLayer();
    virtual ~GameObjectLayer();
    virtual bool init();
    virtual void update(float dt);
    virtual void draw();
    
    GameMatch* gameMatch;
    
    Character* getCharacter();
    
    CC_SYNTHESIZE(CharacterActionEngine*, characterActionEngine, CharacterActionEngine);
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
    CCString *text;
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    virtual bool removeSubController(Controller* controller);

    CREATE_FUNC(GameObjectLayer);

    
};

#endif /* defined(__SampleCocosProject__GameObjectLayer__) */
