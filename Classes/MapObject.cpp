//
//  MapObject.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#include "MapObject.h"

MapObject::MapObject()
{
    this->gameObjectID = MAP_OBJECT;
    this->canPass = false;
}

MapObject::~MapObject()
{
    
}

void MapObject::update(float dt)
{

  //  GameObject::update(dt);

}

void MapObject::onCreate()
{
    PhysicData* data = new PhysicData();//= new PhysicData();
    data->Id = MAP_BASE;
    data->GameObjectID = MAP_OBJECT;
    data->Data = this;
    this->body->SetUserData(data);
    
    this->setGroup(TERRAIN);
}