//
//  ObjectFactory.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#ifndef __SampleCocosProject__ObjectFactory__
#define __SampleCocosProject__ObjectFactory__

#include <iostream>
#include "Character.h"
#include "MapObject.h"
#include "MapObjectDTO.h"

class ObjectFactory
{
public:
    ObjectFactory();
    ~ObjectFactory();

    static ObjectFactory* getSharedManager();
    
    Character* createCharacter(const std::string &name, b2World *world);
    MapObject* createMapObject(const char *idMapObject, b2World *world);
    MapObject* createMapObject(MapObjectDTO* mapObjectDTO, b2World *world);
};

#endif /* defined(__SampleCocosProject__ObjectFactory__) */
