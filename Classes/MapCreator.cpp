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
    
    //    //create background
    //    map->addParallaxBackground(createParallaxBackground(mapDTO->listBackgroundDTO,mapDTO->width,mapDTO->height));
    //    //create foreground
    //    map->addParallaxForeground(createParallaxForeground(mapDTO->listForegroundDTO,mapDTO->width,mapDTO->height));
    
    ///////////////////////////////////
    ///////////////////////////////////
    
    MapObject* mapObject = NULL;
    
    //sprite
    CCSprite* sprite = CCSprite::createWithSpriteFrameName("map1_1.png");
    
    
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    
    b2PolygonShape shape;
    shape.SetAsBox(4, 4);
    
    b2FixtureDef fix;
    fix.shape = &shape;
    fix.density = 2;
    
   


    
    
    
    
    b2Body *body = gameWorld->getWorld()->CreateBody(&bodyDef);
    //set data id
    body->SetUserData((void *) MAP_BASE);
    body->CreateFixture(&fix);
    
    ///
    
    
    b2PolygonShape shapeJoint;
    shape.SetAsBox(1, 1);
    
    b2FixtureDef fixDefJoint;
    fixDefJoint.shape = &shape;
    fixDefJoint.density=1;
    
    b2BodyDef bodyDefJoint;
    bodyDef.type =b2_kinematicBody;
    bodyDef.fixedRotation = true;
    
   // b2Body* bodyJoint = gameWorld->getWorld()->CreateBody(<#const b2BodyDef *def#>)
    ///
    
    
    
    //set data id
    PhysicData* data = new PhysicData();
    data->Id = MAP_BASE;
    data->Data = NULL;
    body->SetUserData(data);
    
    mapObject = MoveableMapObject::create();
    
    
    mapObject->setSkin(body, sprite);
    mapObject->setPositionInPixel(ccp(500  ,800));
    
    map->addMapObject(mapObject);
    /////////////////////////////////
    //////////////////////////////////
  
    
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


