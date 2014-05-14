//
//  EffectData.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/16/14.
//
//

#ifndef __TinyZodiacs__EffectData__
#define __TinyZodiacs__EffectData__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"
#include "PhysicConstants.h"

USING_NS_CC;
class EffectData: public CCObject
{
private:
protected:
public:
    EffectData();
    ~EffectData();
    
    CC_SYNTHESIZE(std::string, animationId, AnimationId);
    CC_SYNTHESIZE(int, animationLayerIndex, AnimationLayerIndex);
    CC_SYNTHESIZE(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE(JointDef, jointDefB, JointDefB);

    CC_SYNTHESIZE(float, chance, Chance);
    CC_SYNTHESIZE(float, critChance, CritChance);
    CC_SYNTHESIZE(float, critRatio, CritRatio);
    
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, attack, Attack);
    CC_SYNTHESIZE(int, speed, Speed);
    CC_SYNTHESIZE(int, attackSpeed, AttackSpeed);
    CC_SYNTHESIZE(int, maxJump, MaxJump);
    CC_SYNTHESIZE(int, jumpHeight, JumpHeight);
    CC_SYNTHESIZE(int, defense, Defense);
    
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CC_SYNTHESIZE(float, timeTick, timeTick);
    
    EffectData* clonePointer();
    EffectData clone();

};
#endif /* defined(__TinyZodiacs__EffectData__) */
