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

USING_NS_CC;
class NormalProjectile: public GameObject
{
private:
protected:
    virtual void checkCollisionDataInBeginContact(PhysicData* data);
    virtual void checkCollisionDataInEndContact(PhysicData* data);
public:
    ~NormalProjectile();
    
    CC_SYNTHESIZE(SkillData*, data, Data);
};
#endif /* defined(__TinyZodiacs__NormalProjectile__) */
