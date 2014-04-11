//
//  NormalProjectile.h
//  TinyZodiacs
//
//  Created by Nhut on 3/20/14.
//
//

#ifndef __TinyZodiacs__NormalProjectile__
#define __TinyZodiacs__NormalProjectile__

#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "GameObject.h"
#include "SkillData.h"
#include "PhysicBodyManager.h"
#include "ScheduleManager.h"
#include "NormalShootingSkillData.h"

USING_NS_CC;
class NormalProjectile: public GameObject
{
private:
protected:
    int contact_count;
    
    virtual void checkCollisionDataInBeginContact(PhysicData* data);
    virtual void checkCollisionDataInEndContact(PhysicData* data);
    
    virtual void remove();
    
    bool scheduled;
public:
    NormalProjectile(NormalShootingSkillData data, GameObject* holder);
    ~NormalProjectile();
    
    CC_SYNTHESIZE(NormalShootingSkillData, data, Data);
    CC_SYNTHESIZE_READONLY(b2Body*, body, Body);
    
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void update(float dt);
    
    virtual void setGroup(int group);

    virtual void excuteScheduledFunction(CCObject* pSender, void *body);
};
#endif /* defined(__TinyZodiacs__NormalProjectile__) */
