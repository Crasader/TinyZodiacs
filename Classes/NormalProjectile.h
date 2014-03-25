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
#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "PhysicConstants.h"
#include "GameObject.h"
#include "SkillData.h"
#include "PhysicBodyManager.h"

USING_NS_CC;
class NormalProjectile: public GameObject
{
private:
    int contact_count;
protected:
    virtual void checkCollisionDataInBeginContact(PhysicData* data);
    virtual void checkCollisionDataInEndContact(PhysicData* data);
    
    virtual void remove();
public:
    NormalProjectile();
    ~NormalProjectile();
    
    CC_SYNTHESIZE(SkillData*, data, Data);
    CREATE_FUNC(NormalProjectile);
    
    virtual bool init();
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);
};
#endif /* defined(__TinyZodiacs__NormalProjectile__) */
