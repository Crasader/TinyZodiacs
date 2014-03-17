//
//  Character.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__Character__
#define __SampleCocosProject__Character__

#include <iostream>
#include "GameObject.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AnimationObject.h"
#include "CharacterData.h"


class CharacterState;

class Character: public GameObject
{
private:
    float speed;
    b2Body* skillSensorBody;
    void setupJointSkillAndBody();
    void createFootSensor();
    CharacterState* state;
protected:
    CC_SYNTHESIZE(CharacterData, originCharacterData, OriginCharacterData);
    CC_SYNTHESIZE(b2Body*, footSensor, FootSensor);
public:
    
    AnimationObject* runAnimation;
    AnimationObject* jumpAnimation;
    AnimationObject* attackAnimation;
    AnimationObject* idleAnimation;
    AnimationObject* flyAnimation;
    AnimationObject* fallAnimation;
    AnimationObject* skill1Animation;
    AnimationObject* skill2Animation;
    
    Character();
    ~Character();
    
    virtual void setSkin(b2Body* body,cocos2d::CCSprite* sprite);
    
    void update(float dt);
    
    void changeState(CharacterState* state);
    
    void move(Direction direction);
    void jump();
    void attack();
    void useSkill1();
    void useSkill2();
    void stopMove();
};

#endif /* defined(__SampleCocosProject__Character__) */
