//
//  SkillData.h
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#ifndef __TinyZodiacs__SkillData__
#define __TinyZodiacs__SkillData__

#include <iostream>
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "Constants.h"
#include "Affect.h"
#include "SkillSoundData.h"
#include "SkillAnimationData.h"

USING_NS_CC;

class SkillData
{
private:
protected:
public:
    SkillData();
    ~SkillData();
//    CC_SYNTHESIZE(AnimationObject*, skillAnimation, SkillAnimation);
    CC_SYNTHESIZE(SkillAnimationData, skillAnimationData, SkillAnimationData);
    CC_SYNTHESIZE(ApplyType, applyType, ApplyType);
    CC_SYNTHESIZE(TextureSelector, skillTextureSelector, skillTextureSelector);
    CC_SYNTHESIZE(float, coolDown, CoolDown);
    CC_SYNTHESIZE(float, delay, Delay);
    CC_SYNTHESIZE(float, lifeTime, LifeTime);
    CC_SYNTHESIZE(JointDef, jointDefA, JointDefA);
    CC_SYNTHESIZE(JointDef, jointDefB, JointDefB);
    CC_SYNTHESIZE(SkillTarget, target, Target)
    CC_SYNTHESIZE(vector<EffectData>, listEnemyEffect, ListEnemyEffect);
    CC_SYNTHESIZE(vector<EffectData>, listAlliesEffect, ListAlliesEffect);
    CC_SYNTHESIZE(vector<EffectData>, listSelfEffect, listSelfEffect);
    CC_SYNTHESIZE(float, timeTick, TimeTick);
    CC_SYNTHESIZE(SkillSoundData, soundData, SoundData);
    
    void releaseEffectLists();
    virtual void clone();
};
#endif /* defined(__TinyZodiacs__SkillData__) */
