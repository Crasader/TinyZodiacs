//
//  PhysicData.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__PhysicData__
#define __Headball__PhysicData__

#include <iostream>
#include "PhysicConstants.h"

class PhysicData
{
private:
protected:
public:
    PhysicData();
    ~PhysicData();
    BodyId bodyId;
    FixtureID fixtureId;
    GameObjectID gameObjectID;
    void* data;
};
#endif /* defined(__Headball__PhysicData__) */
