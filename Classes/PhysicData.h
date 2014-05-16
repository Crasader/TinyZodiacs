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
    BodyId BodyId;
    FixtureID FixtureId;
    GameObjectID GameObjectID;
    void* Data;
};
#endif /* defined(__Headball__PhysicData__) */
