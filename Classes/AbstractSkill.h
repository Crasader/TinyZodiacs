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

USING_NS_CC;
class AbstractSkill: public CCObject
{
private:
protected:
public:
    ~AbstractSkill();
    
    virtual void excute() =0;
    virtual void stop() =0;
    virtual void BeginContact(b2Contact *contact) =0;
    virtual void EndContact(b2Contact *contact) =0;
    
    CC_SYNTHESIZE(GameObject* , holder, Holder);
    CC_SYNTHESIZE(b2Body*, skillSensor, SkillSensor);
    CC_SYNTHESIZE(CCPoint, position, Position) //Position
};
#endif /* defined(__TinyZodiacs__AbstractSkill__) */
