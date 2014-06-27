//
//  EffectData.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/16/14.
//
//

#include "EffectData.h"

EffectData::EffectData()
{
    this->autorelease();
}

EffectData::~EffectData()
{
}

//EffectData* EffectData::clonePointer()
//{
//    EffectData* effectData = new EffectData();
//    effectData->setAnimationId(this->animationId);
//    effectData->setAnimationLayerIndex(this->animationLayerIndex);
//    effectData->setJointDefA(this->jointDefA);
//    effectData->setJointDefB(this->jointDefB);
//    
//    effectData->setChance(this->chance);
//    effectData->setCritChance(this->critChance);
//    effectData->setCritRatio(this->critRatio);
//    
//    effectData->setHealth(this->health);
//    effectData->setAttack(this->attack);
//    effectData->setSpeed(this->speed);
//    effectData->setAttackSpeed(this->attackSpeed);
//    effectData->setMaxJump(this->maxJump);
//    effectData->setJumpHeight(this->jumpHeight);
//    effectData->setDefense(this->defense);
//    
//    effectData->setLifeTime(this->lifeTime);
//    effectData->settimeTick(this->timeTick);
//
//    return effectData;
//}

EffectData EffectData::clone()
{
    EffectData effectData;
    effectData.setAnimationId(this->animationId);
    effectData.setAnimationLayerIndex(this->animationLayerIndex);
    effectData.setMinRotateAngle(this->minRotateAngle);
    effectData.setMaxRotateAngle(this->maxRotateAngle);
    effectData.setMinScale(this->minScale);
    effectData.setMaxScale(this->maxScale);
    effectData.setRepeatTimes(this->repeatTimes);
    effectData.setJointDefA(this->jointDefA);
    effectData.setJointDefB(this->jointDefB);
    
    effectData.setChance(this->chance);
    effectData.setCritChance(this->critChance);
    effectData.setCritRatio(this->critRatio);
    
    effectData.setHealth(this->health);
    effectData.setAttack(this->attack);
    effectData.setSpeed(this->speed);
    effectData.setAttackSpeed(this->attackSpeed);
    effectData.setMaxJump(this->maxJump);
    effectData.setJumpHeight(this->jumpHeight);
    effectData.setDefense(this->defense);
    
    effectData.setLifeTime(this->lifeTime);
    effectData.settimeTick(this->timeTick);
    effectData.setSoundEffect(this->soundEffect);
    
    return effectData;
}