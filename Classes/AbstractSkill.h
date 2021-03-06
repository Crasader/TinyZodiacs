//
//  AbstractSkill.h
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#ifndef __TinyZodiacs__AbstractSkill__
#define __TinyZodiacs__AbstractSkill__

class AbstractSkill;

#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "GameObject.h"
#include "SkillData.h"
#include "ControllerManager.h"
#include "CharacterData.h"

USING_NS_CC;

class AbstractSkill: public CCObject
{
private:
protected:
    CC_SYNTHESIZE(bool, isDisable, IsDisable);
    CC_SYNTHESIZE_READONLY(bool, isExcutable, IsExcutable);
    
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact) = 0;
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact) = 0;
    
    virtual void checkCollisionDataInPreSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2Manifold* oldManifold);
    virtual void checkCollisionDataInPostSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2ContactImpulse* impulse);
    
    virtual void setExcuteAble() = 0;
    
    CCAction *excuteAction, *stopAction, *coolDownAction;
    
    virtual void calculateSkillData(SkillData* data, CharacterData characterData);
    
    virtual void playSFX(const char* sfxName);
    virtual void stopSFX(unsigned int sfxid);
    virtual void playSoundByState(SkillState soundState, SkillSoundData data);
    virtual void changeState(SkillState state);
    
    SkillState currentState;
public:
    AbstractSkill(GameObject* holder, SkillData data);

    ~AbstractSkill();
    
    virtual void excute();
    virtual void stop();
    virtual void update(float dt) = 0;
    virtual void excuteImmediately();
    virtual void stopImmediately();
    virtual void onCreate() = 0;
    virtual void destroy() = 0;
    
    virtual void setPhysicGroup(uint16 group) = 0;
    virtual void stopAllAction();
    
    virtual void playAnimationByState(SkillState state);
    
    virtual void stopSkillSafely();
    
    CC_SYNTHESIZE(GameObject* , holder, Holder);
    CC_SYNTHESIZE(ButtonID, skillButtonID, SkillButtonID);
    CC_SYNTHESIZE(TextureSelector, skillTextureSelector, SkillTextureSelector);
};
#endif /* defined(__TinyZodiacs__AbstractSkill__) */
