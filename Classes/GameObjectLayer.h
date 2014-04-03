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

class GameObjectLayer: public cocos2d::CCLayer
{
public:
    GameObjectLayer();
    virtual ~GameObjectLayer();
    virtual bool init();
    virtual void update(float dt);
    virtual void draw();
    
    void MoveSpriteLeft();
    void MoveSpriteRight();
    void MoveSpriteUp();
    void MoveSpriteDown();
    void MoveSprite(float x, float y);
    void Attack();
    void Skill1();
    void Skill2();

    
    CC_SYNTHESIZE(CharacterActionEngine*, characterActionEngine, CharacterActionEngine);
    
    CREATE_FUNC(GameObjectLayer);

private:
    GameWorld* gameWorld;

  
    
    
    
};

#endif /* defined(__SampleCocosProject__GameObjectLayer__) */
