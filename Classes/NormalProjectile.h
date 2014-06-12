//
//  NormalProjectile.h
//  TinyZodiacs
//
//  Created by Nhut on 3/20/14.
//
//

#ifndef __TinyZodiacs__NormalProjectile__
#define __TinyZodiacs__NormalProjectile__

class NormalProjectile;

#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "GameObject.h"
#include "SkillData.h"
#include "NormalShootingSkillData.h"
#include "Observer.h"

USING_NS_CC;

class NormalProjectile: public GameObject, public Observer
{
private:
    b2Vec2 holderSpeed;
    b2Vec2 getGlobalBodyStartPosition(GameObject* holder, JointDef jointDef);
    
//    CCParticleSystemQuad* p;
protected:
    CCAction* lifeTimeScheduled;
    
    CCAction* timeTickAction;
    CCArray* listTarget;
    
    bool isDisable;
    
    virtual b2Vec2 getStartPosition(GameObject* holder, b2Body* me);
    virtual void changeCreatAnimationToShootingAnimation();
    
    virtual void applyEffectOnTimeTick();
    
    virtual bool shouldDestroy();
public:
    NormalProjectile();
    ~NormalProjectile();
    
    void setData(NormalShootingSkillData data, GameObject* holder);
    
    virtual bool init();
    CREATE_FUNC(NormalProjectile);
    
    CC_SYNTHESIZE(NormalShootingSkillData, data, Data);
    CC_SYNTHESIZE(Group, group, Group);
    
    virtual void initData(NormalShootingSkillData data, GameObject* holder, uint16 group);
    virtual void initDataAndShoot(NormalShootingSkillData data, GameObject* holder, uint16 group);
    
    virtual void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    virtual void update(float dt);
    
    virtual void setGroup(uint16 group);
    virtual void destroy();
    
    void shoot();
    
    void notifyToDestroy(GameObject* object);
};
#endif /* defined(__TinyZodiacs__NormalProjectile__) */
