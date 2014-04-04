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


USING_NS_CC;
class NormalShootingAttack: public AbstractSkill
{
private:
protected:
    CCArray* listProjectiles;
    
    virtual void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    virtual void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);
public:
    ~NormalShootingAttack();
    NormalShootingAttack(GameObject* holder);
    
    virtual void excute();
    virtual void stop();
    virtual void update(float dt);
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);

};
#endif /* defined(__TinyZodiacs__NormalShootingAttack__) */
