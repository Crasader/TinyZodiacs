//
//  MapCreator.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#include "MapCreator.h"
#include "MoveableMapObject.h"
#include "MonsterFactoryDTO.h"


MapCreator::MapCreator()
{
    
}

MapCreator::~MapCreator()
{
    
}

Map* MapCreator::createMap(MapDTO* mapDTO, GameWorld* gameWorld)
{
    Map* map =  Map::create();
    map->setMapDTO(mapDTO);
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
        
        MapObject* mapObject = ObjectFactory::createMapObject(mapObjectDTO, gameWorld->getWorld());
        
        map->addMapObject(mapObject);
    }
    
    object = NULL;
    CCARRAY_FOREACH(mapDTO->listSensorObjectDTO, object)
    {
        SensorObjectDTO* sensorObjectDTO = dynamic_cast<SensorObjectDTO*>(object);
        
        SensorObject* sensorObject = ObjectFactory::createSensorObject(sensorObjectDTO, gameWorld->getWorld());
        
        map->addSensorObject(sensorObject);
    }
    
    object = NULL;
    CCARRAY_FOREACH(mapDTO->listItemCreatorDTO, object)
    {
        ItemCreatorDTO* itemCreatorDTO = dynamic_cast<ItemCreatorDTO*>(object);
        
        ItemCreator* itemCreator = ObjectFactory::createItemCreator(itemCreatorDTO);
        
        map->addItemCreator(itemCreator);
    }
    
    object = NULL;
    CCARRAY_FOREACH(mapDTO->listWaveDTO, object)
    {
        WaveDTO* waveDTO = static_cast<WaveDTO*>(object);
        
        Wave* wave = createWave(waveDTO, gameWorld);
        
        map->addWave(wave);
    }
    
        //    //create background
       map->addParallaxBackground(createParallaxBackground(mapDTO->listBackgroundDTO,mapDTO->width,mapDTO->height));
//        //    //create foreground
        map->addParallaxForeground(createParallaxForeground(mapDTO->listForegroundDTO,mapDTO->width,mapDTO->height));
    
    return map;
    
}

Map* MapCreator::createMap(const char *id, GameWorld* gameWorld)
{
    return createMap(DataCollector::getInstance()->getMapDTOByKey(id), gameWorld);
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

MapParallaxForeground* MapCreator::createParallaxForeground(CCArray* listForegroundDTO, float width, float height)
{
    MapParallaxForeground* parallaxForeground = MapParallaxForeground::create();
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(listForegroundDTO, object)
    {
        ForegroundDTO* foregroundDTO = dynamic_cast<ForegroundDTO*>(object);
        
        parallaxForeground->addForeground(foregroundDTO->imageName,"",foregroundDTO->ratioX, foregroundDTO->ratioY, foregroundDTO->layerIndex, foregroundDTO->positionX, foregroundDTO->positionY);
    }
    
    return parallaxForeground;
}

Wave* MapCreator::createWave(WaveDTO* waveDTO, GameWorld* gameWorld)
{
    Wave* wave = Wave::create();
    
    CCObject* object = NULL;
    
    CCARRAY_FOREACH(waveDTO->listMonsterFactoryDTO, object)
    {
        MonsterFactoryDTO* monsterFactoryDTO = static_cast<MonsterFactoryDTO*>(object);
        if(monsterFactoryDTO != NULL)
        {
            if(monsterFactoryDTO->group == B)
            {
                
                MonsterFactory* monsterFactory = MonsterFactory::create();
                monsterFactory->setHolder(GameManager::getInstance()->getGameplayHolder());
                monsterFactory->setGroup(B);
                
                CCObject* object1 = NULL;
                CCARRAY_FOREACH(monsterFactoryDTO->listMonsterCreatorDTO, object1)
                {
                    MonsterCreatorDTO* monsterCreatorDTO = dynamic_cast<MonsterCreatorDTO*>(object1);
                    monsterFactory->registerMonsterCreator(monsterCreatorDTO, gameWorld->getWorld());
                }
                
                wave->addMonsterFactory(monsterFactory);
            }
        }
    }
    
    object = NULL;
    
    CCARRAY_FOREACH(waveDTO->listItemCreatorDTO, object)
    {
        ItemCreatorDTO* itemCreatorDTO = static_cast<ItemCreatorDTO*>(object);
        if(itemCreatorDTO != NULL)
        {
            wave->addItemCreator(ObjectFactory::createItemCreator(itemCreatorDTO));
        }
    }

    
    return wave;
}

