//
//  Affect.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/18/14.
//
//

#ifndef __TinyZodiacs__Affect__
#define __TinyZodiacs__Affect__

class Affect;

#include <iostream>
#include "cocos2d.h"
#include "EffectData.h"
#include "GameObject.h"
#include "SkillAnimationEffect.h"

USING_NS_CC;

class Affect: public CCObject
{
private:
    bool isDestroyed;
protected:
    CCAction* timeTickRepeatAction;
    CCAction* lifeTimeAction;
    CCSize positionOffset;
    
    CC_SYNTHESIZE_READONLY(GameObject*, holder, Holder);
//    CC_SYNTHESIZE_READONLY(CCSprite*, sprite, Sprite);
    
    CCPoint calculatePosition(JointDef jointDefA, JointDef jointDefB);
    CCPoint calculate(CCSize boudingBox, int typeX, int typeY, float offsetX, float offsetY);
    
    void destroy();
    void destroyOnTimeOut();

    void onTimeTick();
    
    void setDataAfterFirstTick();
public:
    CC_SYNTHESIZE_READONLY(SkillAnimationEffect*, animation, Animation);
    CC_SYNTHESIZE_READONLY(int, animationLayerIndex, AnimationLayerIndex);
    CC_SYNTHESIZE_READONLY(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE_READONLY(JointDef, jointDefB, JointDefB);
    
    CC_SYNTHESIZE_READONLY(float, chance, chance);
    CC_SYNTHESIZE_READONLY(float, critChance, CritChance);
    CC_SYNTHESIZE_READONLY(float, critRatio, CritRatio);
    
    CC_SYNTHESIZE_READONLY(int, health, Health);
    CC_SYNTHESIZE_READONLY(int, attack, Attack);
    CC_SYNTHESIZE_READONLY(int, speed, Speed);
    CC_SYNTHESIZE_READONLY(int, attackSpeed, AttackSpeed);
    CC_SYNTHESIZE_READONLY(int, maxJump, MaxJump);
    CC_SYNTHESIZE_READONLY(int, jumpHeight, JumpHeight);
    CC_SYNTHESIZE_READONLY(int, defense, Defense);
    
    CC_SYNTHESIZE_READONLY(float, lifeTime, LifeTime);
    CC_SYNTHESIZE_READONLY(float, timeTick, timeTick);
    CC_SYNTHESIZE_READONLY(std::string, soundEffect, SoundEffect);
    
    Affect();
    ~Affect();
    
    void start();
    
    virtual bool init();
    
    void stopAllSchedule();
    
    void update(float dt);
    void setData(EffectData effectData);
    void setHolder(GameObject* holder);
    
    CREATE_FUNC(Affect);
    
};
#endif /* defined(__TinyZodiacs__Affect__) */
