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

USING_NS_CC;
class NormalAttack: public AbstractSkill
{
private:
protected:
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact);
public:
    NormalAttack();
    NormalAttack(GameObject* holder);
    ~NormalAttack();
    
    virtual void excute();
    virtual void stop();
    virtual void update(float dt);
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
};
#endif /* defined(__TinyZodiacs__NormalAttack__) */
