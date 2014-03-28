//
//  NormalAttack.h
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#ifndef __TinyZodiacs__NormalAttack__
#define __TinyZodiacs__NormalAttack__

#include <iostream>
#include "AbstractSkill.h"
#include "NormalMeleeSkillData.h"

USING_NS_CC;
class NormalAttack: public AbstractSkill
{
private:
    char holder_join_type;
    char this_join_type;
    
    b2RevoluteJointDef skillJoint;
protected:
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact);
public:
    NormalAttack(GameObject* holder, NormalMeleeSkillData data);
    ~NormalAttack();
    
    CC_SYNTHESIZE(NormalMeleeSkillData, data, Data);
    
    virtual void excute();
    virtual void stop();
    virtual void update(float dt);
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    
    virtual void excuteImmediately();
    virtual void flip();
};
#endif /* defined(__TinyZodiacs__NormalAttack__) */
