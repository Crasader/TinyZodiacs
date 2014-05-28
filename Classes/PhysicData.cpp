//
//  PhysicData.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "PhysicData.h"

PhysicData::PhysicData()
{
    gameObjectID = NONE;
    bodyId = MAP_BASE;
    fixtureId = FOOT_SENSOR;
    data = NULL;
}

PhysicData::~PhysicData()
{
    
}