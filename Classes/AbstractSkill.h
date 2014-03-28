//
//  AbstractSkill.h
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#ifndef __TinyZodiacs__AbstractSkill__
#define __TinyZodiacs__AbstractSkill__

#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "GameObject.h"
#include "SkillData.h"

USING_NS_CC;
class AbstractSkill: public CCObject
{
private:
protected:
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact)=0;
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact)=0;
public:
    ~AbstractSkill();
    
    virtual void excute() =0;
    virtual void stop() =0;
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
    virtual void update(float dt)=0;
    virtual void excuteImmediately();
    virtual void stopImmediately();

    virtual void flip();
    
    CC_SYNTHESIZE(GameObject* , holder, Holder);
};
#endif /* defined(__TinyZodiacs__AbstractSkill__) */
