//
//  MapCreator.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#include "MapCreator.h"


MapCreator::MapCreator()
{
    
}

MapCreator::~MapCreator()
{
    
}

Map* MapCreator::createMap(const char *id, GameWorld* gameWorld)
{
    
    MapDTO* mapDTO = MapFactory::getSharedFactory()->getMapByName(id);
    
    Map* map =  Map::create();
    map->retain();
    
    map->setWidth(mapDTO->width);
    map->setHeight(mapDTO->height);
    gameWorld->setWidth(mapDTO->width);
    gameWorld->setHeight(mapDTO->height);
    
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(mapDTO->listMapObject, object)
    {
        MapObjectDTO* mapObjectDTO = dynamic_cast<MapObjectDTO*>(object);
        
        MapObject* mapObject = ObjectFactory::getSharedManager()->createMapObject(mapObjectDTO, gameWorld->getWorld());
        
        map->addMapObject(mapObject);
        
    }
    
    return map;
    
}