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
protected:
    CCCallFunc* autoShootAction;
    GameObjectCalculateData calculatedGameObjectData;
    
    int shootedTime;
    
    CC_SYNTHESIZE(NormalShootingSkillData, data, Data);

    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    
    virtual void setExcuteAble();
    virtual void autoShoot();
    
    virtual void stopAllAction();
public:
    NormalShootingAttack(GameObject* holder, NormalShootingSkillData data);
    ~NormalShootingAttack();
 
    virtual void excute();
    virtual void excuteImmediately();
    virtual void stop();
    virtual void stopImmediately();
    virtual void update(float dt);
    virtual void onCreate();
    virtual void destroy();

    virtual void setPhysicGroup(uint16 group);
};
#endif /* defined(__TinyZodiacs__NormalShootingAttack__) */
