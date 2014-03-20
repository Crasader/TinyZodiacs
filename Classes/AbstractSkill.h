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
    virtual void Update(float dt)=0;
    
    CC_SYNTHESIZE(GameObject* , holder, Holder);
    CC_SYNTHESIZE(SkillData, data, Data);
};
#endif /* defined(__TinyZodiacs__AbstractSkill__) */
