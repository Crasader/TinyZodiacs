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
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "Character.h"

USING_NS_CC;
class NormalAttack: public CCObject
{
private:

protected:
public:
    NormalAttack();
    NormalAttack(GameObject* holder);
    ~NormalAttack();
    
    virtual void excute();
    virtual void stop();
    
    CC_SYNTHESIZE(GameObject* , holder, Holder);
    CC_SYNTHESIZE(b2Body*, skillSensor, SkillSensor);
    CC_SYNTHESIZE(CCPoint, position, Position) //Position
};
#endif /* defined(__TinyZodiacs__NormalAttack__) */
