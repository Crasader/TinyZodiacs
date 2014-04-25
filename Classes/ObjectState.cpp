//
//  ObjectState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "ObjectState.h"

ObjectState::ObjectState()
{
    //this->onEnterState();
}

ObjectState::~ObjectState()
{
   // this->onExitState();
}

bool ObjectState::onEnterState()
{
    return true;
}

bool ObjectState::onExitState()
{
    return true;
}