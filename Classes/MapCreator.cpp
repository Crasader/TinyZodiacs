//
//  MapCreator.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#include "MapCreator.h"
#include "MoveableMapObject.h"


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
    
    // create map object
    CCObject* object = NULL;
    CCARRAY_FOREACH(mapDTO->listMapObjectDTO, object)
    {
        MapObjectDTO* mapObjectDTO = dynamic_cast<MapObjectDTO*>(object);
        
        MapObject* mapObject = ObjectFactory::getSharedManager()->createMapObject(mapObjectDTO, gameWorld->getWorld());
        
        map->addMapObject(mapObject);
    }
    
    object = NULL;
    CCARRAY_FOREACH(mapDTO->listSensorObjectDTO, object)
    {
        SensorObjectDTO* sensorObjectDTO = dynamic_cast<SensorObjectDTO*>(object);
        
        SensorObject* sensorObject = ObjectFactory::getSharedManager()->createSensorObject(sensorObjectDTO, gameWorld->getWorld());
   
        map->addSensorObject(sensorObject);
    }

    
    
    //    //create background
    //    map->addParallaxBackground(createParallaxBackground(mapDTO->listBackgroundDTO,mapDTO->width,mapDTO->height));
    //    //create foreground
    //    map->addParallaxForeground(createParallaxForeground(mapDTO->listForegroundDTO,mapDTO->width,mapDTO->height));
    
    return map;
}

MapParallaxBackground* MapCreator::createParallaxBackground(CCArray* listBackgroundDTO, float width, float height)
{
    MapParallaxBackground* parallaxBackground = MapParallaxBackground::create();
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(listBackgroundDTO, object)
    {
        BackgroundDTO* backgroundDTO = dynamic_cast<BackgroundDTO*>(object);
        
        parallaxBackground->addBackground(backgroundDTO->imageName, backgroundDTO->spritesheetName,backgroundDTO->ratioX, backgroundDTO->ratioY, backgroundDTO->orderIndex, width, height);
    }
    
    return parallaxBackground;
}


