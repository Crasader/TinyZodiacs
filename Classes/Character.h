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
    
public:
    
    AnimationObject* runAnimation;
    AnimationObject* jumpAnimation;
    AnimationObject* attackAnimation;
    AnimationObject* idleAnimation;
    AnimationObject* flyAnimation;
    AnimationObject* fallAnimation;
    AnimationObject* skillAnimation;
    
    
    Character();
    ~Character();
    virtual void setSkin(b2Body* body,cocos2d::CCSprite* sprite);
    
    void update(float dt);
    
    void changeState(CharacterState* state);
    
    
    
    
    
    void move(Direction direction);
    void jump();
    void attack();
    void useSkill1();
    void stopMove();
    
    
    
};

#endif /* defined(__SampleCocosProject__Character__) */
