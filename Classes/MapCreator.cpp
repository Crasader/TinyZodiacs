//
//  MapCreator.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#include "MapCreator.h"
#include "Map.h"
#include "ObjectFactory.h"

MapCreator::MapCreator()
{
    
}

MapCreator::~MapCreator()
{
    
}

Map* MapCreator::createMap(const char *id)
{
    Map* map =  Map::create();
    map->retain();
    

    //FAKE
    MapObject* map1 = ObjectFactory::getSharedManager()->createMapObject("map_1", map->getWorld());
    map1->setPositionInPixel(ccp(400,100));

    MapObject* map2 = ObjectFactory::getSharedManager()->createMapObject("map_2", map->getWorld());
    map2->setPositionInPixel(ccp(500,500));

    MapObject* map3 = ObjectFactory::getSharedManager()->createMapObject("map_3", map->getWorld());
    map3->setPositionInPixel(ccp(600,700));
  
    MapObject* map4 = ObjectFactory::getSharedManager()->createMapObject("map_4", map->getWorld());
    map4->setPositionInPixel(ccp(600,200));
    

    MapObject* map5 = ObjectFactory::getSharedManager()->createMapObject("map_5", map->getWorld());
 map5->setPositionInPixel(ccp(1000,200));
//
//    
    map->addMapObject(map1);
    map->addMapObject(map2);
    map->addMapObject(map3);
    map->addMapObject(map4);
   map->addMapObject(map5);
//
    
    return map;
    
}