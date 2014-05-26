//
//  Character.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__Character__
#define __SampleCocosProject__Character__

class Character;

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"
#include "Box2D/Box2D.h"
#include "AnimationObject.h"
#include "CharacterData.h"
#include "NormalAttack.h"
#include "PhysicData.h"
#include "MapObject.h"
#include "Observable.h"
#include "CharacterState.h"

class Character: public GameObject
{
private:    
    CharacterState* state;

    void setupJointSkillAndBody();
    void createFootSensor();
    bool isCharacterCanPassThoughMapObject(MapObject* mapObject);
protected:
    int currentJumpCount;
    
    void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    
    virtual void setPhysicGroup(uint16 group);
public:
    Character();
    ~Character();
  
    CC_SYNTHESIZE(int, landing, Landing);
    CC_SYNTHESIZE(bool, isLanding, IsLanding);
    CC_SYNTHESIZE_READONLY(CharacterData, originCharacterData, OriginCharacterData);
    CC_SYNTHESIZE(CharacterData, characterData, characterData);
    CC_SYNTHESIZE(b2Fixture*, footSensor, FootSensor);
    CC_SYNTHESIZE(AbstractSkill*, normalAttack, NormalAttack);
    CC_SYNTHESIZE(AbstractSkill*, skill1, Skill1);
    CC_SYNTHESIZE(AbstractSkill*, skill2, Skill2);
    
    AnimationObject* runAnimation;
    AnimationObject* jumpAnimation;
    AnimationObject* attackAnimation;
    AnimationObject* idleAnimation;
    AnimationObject* flyAnimation;
    AnimationObject* fallAnimation;
    AnimationObject* skill1Animation;
    AnimationObject* skill2Animation;
    
    void setOriginCharacterData(CharacterData data);
    void update(float dt);
    void changeState(CharacterState* state);
    virtual void onCreate();
    
    void move(Direction direction);
    void jump();
    void attack();
    void useSkill1();
    void useSkill2();
    void stopMove();
    
    void move(Direction direction, float speed);
    void jump(float force);

    
    virtual void setSkin(b2Body* body,cocos2d::CCSprite* sprite);
    virtual void notifyByAffect(Affect* affect);
    virtual void removeAffect(Affect* affect);
    
    virtual bool isDead();
    
    virtual void destroy();
    
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notifyToDestroy();
};

#endif /* defined(__SampleCocosProject__Character__) */
