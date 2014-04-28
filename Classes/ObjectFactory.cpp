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
#include "MoveableMapObject.h"

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

Character* ObjectFactory::createCharacter(const std::string &name, b2World *world, bool isLocal)
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
    
    Character* character = CharacterFactory::createHero(name,world, isLocal);
    
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
        //        bodyDef.bullet = true;
        //
        b2Body *body = world->CreateBody(&bodyDef);
        sc->addFixturesToBody(body, mapObjectDTO->bodyName.c_str());
        
        sprite->setAnchorPoint(sc->anchorPointForShape(mapObjectDTO->bodyName.c_str()));
        mapObject = MapObject::create();
        
        //set data id
        PhysicData* data = new PhysicData();
        data->Id = MAP_BASE;
        data->Data = mapObject;
        body->SetUserData(data);
        
        
        mapObject->setSkin(body, sprite);
        mapObject->setCanPass(mapObjectDTO->canPass);
        
        mapObject->setGroup(TERRAIN);
    }
    else
    {
        mapObject = NoBodyMapObject::create();
        sprite->setAnchorPoint(ccp(0,0));
        mapObject->setSkin(NULL, sprite);
        
        mapObject->setGroup(TERRAIN);
    }
    
    mapObject->setPositionInPixel(ccp(mapObjectDTO->x,mapObjectDTO->y));
    
    return mapObject;
    
}

SensorObject* ObjectFactory::createSensorObject(b2Vec2 dumb,b2World *world, CCPoint position)
{
    
    SensorObject* sensorObject = NULL;
    sensorObject = SensorObject::create();
    
    b2EdgeShape edge;
    
    edge.Set(b2Vec2(0,0),dumb);
    
    // edge.SetAsBox(1/PTM_RATIO, 4);
    
    b2FixtureDef fixDef;
    fixDef.shape = &edge;
    fixDef.isSensor = true;
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.bullet = true;
    bodyDef.position.Set(10, 3);
    
    b2Body *body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixDef);
    
    
    
    //set data id
    PhysicData* data = new PhysicData();
    data->Id = MAP_SENSOR;
    data->Data = sensorObject;
    
    body->SetUserData(data);
    
    
    sensorObject->setSkin(body, NULL);
    
    sensorObject->setPositionInPixel(position);
    sensorObject->setGroup(TERRAIN);
    
    return sensorObject;
}

SensorObject* ObjectFactory::createSensorObject(SensorObjectDTO* sensorObjectDTO, b2World* world)
{
    SensorObject* sensorObject = SensorObject::create();
    
    sensorObject->setJumpHeight(sensorObjectDTO->jumpHeight);
    sensorObject->setMoveSpeed(sensorObjectDTO->moveSpeed);
    sensorObject->setIsBack(sensorObjectDTO->isBack);
    sensorObject->setMustStop(sensorObjectDTO->mustStop);
    sensorObject->flipDirection(sensorObjectDTO->direction);
    sensorObject->listLaneID = sensorObjectDTO->listLaneID;
    
    b2EdgeShape edge;
    
    edge.Set(b2Vec2(0,0),b2Vec2(sensorObjectDTO->edge_x/PTM_RATIO,sensorObjectDTO->edge_y/PTM_RATIO));
    
    // edge.SetAsBox(1/PTM_RATIO, 4);
    
    b2FixtureDef fixDef;
    fixDef.shape = &edge;
    fixDef.isSensor = true;
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.bullet = true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixDef);
    
    //set data id
    PhysicData* data = new PhysicData();
    data->Id = MAP_SENSOR;
    data->Data = sensorObject;
    
    body->SetUserData(data);
    
    sensorObject->setSkin(body, NULL);
    sensorObject->setPositionInPixel(ccp(sensorObjectDTO->x,sensorObjectDTO->y));
    sensorObject->setGroup(TERRAIN);
    
    return sensorObject;
}

Tower* ObjectFactory::createTower(TowerDTO* towerDTO, b2World* world)
{
    CharacterDTO heroDTOData = CharacterFactory::loadXMLFile(towerDTO->id.c_str());
    
    Tower* tower = Tower::create();
    
    tower->setOriginCharacterData(heroDTOData.data);
    
    //Create Animation
    string run = heroDTOData.animation;
    string attack = heroDTOData.animation;
    string idle = heroDTOData.animation;
    string fall = heroDTOData.animation;
    string fly = heroDTOData.animation;
    string jump = heroDTOData.animation;
    
    tower->runAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(run.append(RUN).c_str());
    tower->attackAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(attack.append(ATTACK).c_str());
    tower->jumpAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(jump.append(JUMP).c_str());
    tower->idleAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(idle.append(IDLE).c_str());
    tower->fallAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fall.append(FALL).c_str());
    tower->flyAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fly.append(FLY).c_str());
    tower->attackAnimation->getAnimation()->setDelayPerUnit(tower->getOriginCharacterData().getAttackSpeed());
    
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    bodyDef.userData = tower;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, heroDTOData.body.c_str());
    tower->setSpriteAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    tower->getSprite()->setAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    tower->setSkin(body, tower->getSprite());
    
    tower->setNormalAttack(SkillFactory::createSkill(heroDTOData.data.getSkill0().c_str(), world, tower, false, SKILL_0_BUTTON));
    tower->setSkill1(SkillFactory::createSkill(heroDTOData.data.getSkill1().c_str(), world, tower, false, SKILL_1_BUTTON));
    tower->setSkill2(SkillFactory::createSkill(heroDTOData.data.getSkill2().c_str(), world, tower, false, SKILL_2_BUTTON));
    
    tower->setPositionInPixel(ccp(towerDTO->x,towerDTO->y));
    if(strcasecmp(towerDTO->group.c_str(),"A") == 0)
    {
        tower->setGroup(A);
    }
    else
    {
        tower->setGroup(B);
    }
    
    return tower;
}
