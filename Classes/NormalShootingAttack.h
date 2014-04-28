//
//  NormalShootingAttack.h
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#ifndef __TinyZodiacs__NormalShootingAttack__
#define __TinyZodiacs__NormalShootingAttack__

#include <iostream>
#include "AbstractSkill.h"
#include "NormalProjectile.h"
#include "NormalShootingSkillData.h"


USING_NS_CC;
class NormalShootingAttack: public AbstractSkill
{
private:
    CCArray* projectTileList;
protected:
    CC_SYNTHESIZE_READONLY(uint16, group, Group);
    CC_SYNTHESIZE(NormalShootingSkillData, data, Data);

    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
    
    virtual void setExcuteAble();
public:
    ~NormalShootingAttack();
    NormalShootingAttack(GameObject* holder, NormalShootingSkillData data);
    
    virtual void excute();
    virtual void stop();
    virtual void update(float dt);
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);

    virtual void excuteImmediately();
    virtual void stopImmediately();
    
    virtual void setPhysicGroup(uint16 group);
};
#endif /* defined(__TinyZodiacs__NormalShootingAttack__) */
