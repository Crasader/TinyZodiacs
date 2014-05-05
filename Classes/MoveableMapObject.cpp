//
//  MoveableMapObject.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/31/14.
//
//

#include "MoveableMapObject.h"

MoveableMapObject::MoveableMapObject()
{
    
}

MoveableMapObject::~MoveableMapObject()
{
    
}

void MoveableMapObject::update(float dt)
{
    //GameObject::update(dt);
    b2Vec2 impulse = this->body->GetLinearVelocity();
   
    {
        impulse.x = 1;
    }
    this->body->SetLinearVelocity(impulse);
    
    
}