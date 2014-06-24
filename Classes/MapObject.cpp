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
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        PhysicData* data = new PhysicData();//= new PhysicData();
        data->bodyId = MAP_BASE;
        data->gameObjectID = MAP_OBJECT;
        data->fixtureId = MAP_OBJECT_FIXTURE;
        data->data = this;
//        this->body->SetUserData(data);
        f->SetUserData(data);
    }
    this->setGroup(TERRAIN);
}