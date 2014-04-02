//
//  ObjectFactory.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/13/14.
//
//

#include "ObjectFactory.h"
#include "cocos2d.h"
#include "GB2ShapeCache-x.h"
#include "MapObject.h"
#include "PhysicConstants.h"
#include "CharacterData.h"
#include "NormalShootingAttack.h"
#include "CharacterFactory.h"

USING_NS_CC;
enum _entityCategory {
    CHARACTER =         0x0002,
    MAPOBJECT =     0x0004,
    
};

static ObjectFactory* sharedFactory = NULL;

ObjectFactory::ObjectFactory()
{
    
}

ObjectFactory::~ObjectFactory()
{
    
}

ObjectFactory* ObjectFactory::getSharedManager()
{
    if (!sharedFactory)
    {
        sharedFactory = new ObjectFactory();
        //  this->sharedFactory->init();
    }
    return sharedFactory;
}

Character* ObjectFactory::createCharacter(const std::string &name, b2World *world)
{
//    Character* character = NULL;
//    character = new Character();
//    
//    //sprite
//    CCSprite* sprite=CCSprite::createWithSpriteFrameName("monkey_idle_1.png");
//    sprite->setScale(0.0f);
//    
//    //body
//    
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.angle = ccpToAngle(ccp(0,0));
//    bodyDef.userData = sprite;
//    bodyDef.fixedRotation=true;
//    
//    b2Body *body = world->CreateBody(&bodyDef);
//    
//    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
//    
//    sc->addFixturesToBody(body, "body");
//    sprite->setAnchorPoint(sc->anchorPointForShape("body"));
//    b2Filter filter = body->GetFixtureList()->GetFilterData();
//    filter.groupIndex = -2;
//    body->GetFixtureList()->SetFilterData(filter);
//    
//    character->setSkin(body, sprite);
//    //TEMP CREATE SKILL
//    character->setNormalAttack(new NormalAttack(character));
//    
//    //set character data
//    CharacterData data;
//    data.setSpeed(10);
//    data.setJumpHeight(50);
//    data.setMaxJumpTimes(3);
//    data.setAttackSpeed(0.1);
//    
//    
//    
//    character->setOriginCharacterData(data);
//    character->attackAnimation->getAnimation()->setDelayPerUnit(data.getAttackSpeed());
//    return character;
    
    Character* character = CharacterFactory::createMonkeyHero(world);
    
    return character;
    
}

MapObject* ObjectFactory::createMapObject(const char *idMapObject, b2World *world)
{
    MapObject* mapObject = NULL;
    
    mapObject = new MapObject();
    
    //sprite
    
    const char* nameSprite = (std::string( idMapObject) + std::string(".png")).c_str();
    
    CCSprite* sprite=CCSprite::createWithSpriteFrameName(nameSprite);
    
    
    
    //body
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.userData = sprite;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, idMapObject);
    sprite->setAnchorPoint(sc->anchorPointForShape(idMapObject));
    
    mapObject->setSkin(body, sprite);
    
    
    return mapObject;
    
}

MapObject* ObjectFactory::createMapObject(MapObjectDTO* mapObjectDTO, b2World *world)
{
    
    
    
    MapObject* mapObject = NULL;
   
    //sprite
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(mapObjectDTO->imageName.c_str());
   
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    if(sc->isBodyExisted(mapObjectDTO->bodyName.c_str()))
    {
        //body
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.angle = ccpToAngle(ccp(0,0));
        
        b2Body *body = world->CreateBody(&bodyDef);
        sc->addFixturesToBody(body, mapObjectDTO->bodyName.c_str());
        //set data id
        body->SetUserData((void *) MAP_BASE);
        sprite->setAnchorPoint(sc->anchorPointForShape(mapObjectDTO->bodyName.c_str()));

        mapObject = MapObject::create();
        mapObject->setSkin(body, sprite);
        
        //set data id
        PhysicData* data = new PhysicData();
        data->Id = MAP_BASE;
        data->Data = NULL;
        body->SetUserData(data);

        mapObject->setGroup(GROUP_TERRAIN);
    }
    else
    {
        mapObject = NoBodyMapObject::create();
        sprite->setAnchorPoint(ccp(0,0));
        mapObject->setSprite(sprite);
    }
    

    
    mapObject->setPositionInPixel(ccp(mapObjectDTO->x,mapObjectDTO->y));
    return mapObject;
    
}




