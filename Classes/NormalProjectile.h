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
#include "NormalShootingSkillData.h"

USING_NS_CC;
class NormalProjectile: public GameObject
{
private:
    b2Vec2 getGlobalBodyStartPosition(b2Body* body, JointDef jointDef);
protected:
//    int contact_count;
//    bool scheduled;
    CCArray* collector;
    CCSequence* lifeTimeScheduled;
    
    virtual void remove();
    virtual b2Vec2 getStartPosition(GameObject* holder, b2Body* me);
public:
    NormalProjectile();
    ~NormalProjectile();
    
    void setData(NormalShootingSkillData data, GameObject* holder, CCArray* collector);
    
    virtual bool init();
    CREATE_FUNC(NormalProjectile);
    
    CC_SYNTHESIZE(NormalShootingSkillData, data, Data);
    CC_SYNTHESIZE_READONLY(GameObject*, holder, Holder);
    
//    virtual void BeginContact(b2Contact *contact);
//    virtual void EndContact(b2Contact *contact);
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void update(float dt);
    
    virtual void setGroup(uint16 group);

    virtual void excuteScheduledFunction(CCObject* pSender, void *body);
};
#endif /* defined(__TinyZodiacs__NormalProjectile__) */
