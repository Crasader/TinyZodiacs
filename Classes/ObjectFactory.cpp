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
#include "MoveableMapObject.h"
#include "DataCollector.h"
#include "SkillFactory.h"
#include "InfoViewCreator.h"

USING_NS_CC;

Hero* ObjectFactory::createHero(HeroDTO* heroDTO, b2World* world, bool isLocal)
{
    Hero* hero = Hero::create();
    createHero(hero, heroDTO);
    return hero;
}

void ObjectFactory::createHero(Hero* hero, HeroDTO* heroDTO)
{
    if(hero != NULL)
    {
        b2World* world = GameManager::getInstance()->getGameplayHolder().worldHolder;
        hero->setOriginCharacterData(heroDTO->data);
        
        //Create Animation
        string run = heroDTO->animation;
        string attack = heroDTO->animation;
        string idle = heroDTO->animation;
        string fall = heroDTO->animation;
        string fly = heroDTO->animation;
        string jump = heroDTO->animation;
        string skill = heroDTO->animation;
        
        hero->runAnimation = DataCollector::getInstance()->getAnimationObjectByKey(string(std::string(run) + std::string(RUN)).c_str());
        hero->attackAnimation = DataCollector::getInstance()->getAnimationObjectByKey(attack.append(ATTACK).c_str());
        hero->jumpAnimation = DataCollector::getInstance()->getAnimationObjectByKey(jump.append(JUMP).c_str());
        hero->idleAnimation = DataCollector::getInstance()->getAnimationObjectByKey(idle.append(IDLE).c_str());
        hero->fallAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fall.append(FALL).c_str());
        hero->flyAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fly.append(FLY).c_str());
        hero->skill1Animation = DataCollector::getInstance()->getAnimationObjectByKey(skill.append(SKILL).c_str());
        
        hero->attackAnimation->getAnimation()->setDelayPerUnit(hero->getOriginCharacterData().getAttackSpeed());
        
        
        //Create body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.angle = ccpToAngle(ccp(0,0));
        bodyDef.fixedRotation = true;
        
        b2Body *body = world->CreateBody(&bodyDef);
        
        gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
        sc->addFixturesToBody(body, heroDTO->body.c_str());
        hero->setSpriteAnchorPoint(sc->anchorPointForShape(heroDTO->body.c_str()));
        hero->getSprite()->setAnchorPoint(sc->anchorPointForShape(heroDTO->body.c_str()));
        hero->setSkin(body, hero->getSprite());
        
        hero->setNormalAttack(SkillFactory::createSkill(heroDTO->data.getSkill0().c_str(), world, hero, true, SKILL_0_BTN));
        hero->setSkill1(SkillFactory::createSkill(heroDTO->data.getSkill1().c_str(), world, hero, true, SKILL_1_BTN));
        hero->setSkill2(SkillFactory::createSkill(heroDTO->data.getSkill2().c_str(), world, hero, true, SKILL_2_BTN));
        hero->setIsControlled(true);
        
        hero->onCreate();
    }
}
MainHero* ObjectFactory::createMainHero(const char* id)
{
    MainHero* mainHero = MainHero::create();
    createHero(mainHero, DataCollector::getInstance()->getHeroDTOByKey(id));
    return mainHero;
}
Hero* ObjectFactory::createHero(const char* id)
{
    Hero* hero = Hero::create();
    createHero(hero, DataCollector::getInstance()->getHeroDTOByKey(id));
    return hero;
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
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, idMapObject);
    sprite->setAnchorPoint(sc->anchorPointForShape(idMapObject));
    
    mapObject->setSkin(body, sprite);
    mapObject->onCreate();
    
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
        mapObject->setSkin(body, sprite);
        mapObject->setCanPass(mapObjectDTO->canPass);
        mapObject->onCreate();
        
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
    
    //set data id
    PhysicData* data = new PhysicData();
    data->bodyId = MAP_SENSOR;
    data->data = sensorObject;
    
    fixDef.userData = data;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.bullet = true;
    bodyDef.position.Set(10, 3);
    
    b2Body *body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixDef);
    
    
    
    //    //set data id
    //    PhysicData* data = new PhysicData();
    //    data->BodyId = MAP_SENSOR;
    //    data->Data = sensorObject;
    //
    //    body->SetUserData(data);
    
    
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
    
    PhysicData* data = new PhysicData();
    data->bodyId = MAP_SENSOR;
    data->data = sensorObject;
    fixDef.userData = data;
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.bullet = true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixDef);
    
    //set data id
    //    PhysicData* data = new PhysicData();
    //    data->BodyId = MAP_SENSOR;
    //    data->Data = sensorObject;
    
    //    body->SetUserData(data);
    
    sensorObject->setSkin(body, NULL);
    sensorObject->setPositionInPixel(ccp(sensorObjectDTO->x,sensorObjectDTO->y));
    sensorObject->setGroup(TERRAIN);
    
    return sensorObject;
}



Tower* ObjectFactory::createTower(TowerStructDTO* towerStructDTO, b2World* world)
{
    TowerDTO* towerDTO = DataCollector::getInstance()->getTowerDTOByKey(towerStructDTO->id.c_str());
    Tower* tower = NULL;
    if(strcasecmp(towerStructDTO->type.c_str(), "main") == 0)
    {
        tower = MainCrystal::create();
        CCLOG("main");
    }
    else
    {
        tower = Tower::create();
        CCLOG("tower");
    }
    
    
    tower->setOriginCharacterData(towerDTO->data);
    
    //Create Animation
    string run = towerDTO->animation;
    string attack = towerDTO->animation;
    string idle = towerDTO->animation;
    string fall = towerDTO->animation;
    string fly = towerDTO->animation;
    string jump = towerDTO->animation;
    
    tower->runAnimation = DataCollector::getInstance()->getAnimationObjectByKey(run.append(RUN).c_str());
    tower->attackAnimation = DataCollector::getInstance()->getAnimationObjectByKey(attack.append(ATTACK).c_str());
    tower->jumpAnimation = DataCollector::getInstance()->getAnimationObjectByKey(jump.append(JUMP).c_str());
    tower->idleAnimation = DataCollector::getInstance()->getAnimationObjectByKey(idle.append(IDLE).c_str());
    tower->fallAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fall.append(FALL).c_str());
    tower->flyAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fly.append(FLY).c_str());
    tower->attackAnimation->getAnimation()->setDelayPerUnit(tower->getOriginCharacterData().getAttackSpeed());
    
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body,  towerDTO->body.c_str());
    tower->setSpriteAnchorPoint(sc->anchorPointForShape(towerDTO->body.c_str()));
    tower->getSprite()->setAnchorPoint(sc->anchorPointForShape(towerDTO->body.c_str()));
    tower->setSkin(body, tower->getSprite());
    
    //
    tower->setSensor(towerDTO->towerSensorId.c_str());
    
    tower->setNormalAttack(SkillFactory::createSkill(towerDTO->data.getSkill0().c_str(), world, tower, false, SKILL_0_BTN));
    //    tower->setSkill1(SkillFactory::createSkill(towerDTO->data.getSkill1().c_str(), world, tower, false, SKILL_1_BUTTON));
    //    tower->setSkill2(SkillFactory::createSkill(towerDTO->data.getSkill2().c_str(), world, tower, false, SKILL_2_BUTTON));
    
    tower->setPositionInPixel(ccp(towerStructDTO->positionX,towerStructDTO->positionY));
    tower->setGroup(towerStructDTO->group);
    tower->onCreate();
    return tower;
}

Item* ObjectFactory::createItem(ItemDTO* itemDTO, b2World* world)
{
    Item* item = NULL;
    
    ItemType itemType = Util::convertStringToItemType(itemDTO->type.c_str());
    
    switch (itemType) {
        case CONTAINER:
            item = createContainerItem(itemDTO, world);
            break;
        case BONUS:
            item = createBonusItem(itemDTO, world);
            break;
        case GOLD:
            item = createGoldItem(itemDTO, world);
            break;
        default:
            break;
    }
    return item;
}

Item* ObjectFactory::createContainerItem(ItemDTO* itemDTO, b2World* world)
{
    ContainerItem* containerItem = ContainerItem::create();
    containerItem->setlistSubItem(itemDTO->listSubItemStruct);
    //
    containerItem->setPrepareToAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToAppear).c_str()));
    containerItem->setAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_appear).c_str()));
    containerItem->setprepareToDisappearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToDisappear).c_str()));
    //sprite
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(itemDTO->imageName.c_str());
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation = true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, itemDTO->bodyName.c_str());
    containerItem->setSkin(body, sprite);
    
    containerItem->setSpriteAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    containerItem->getSprite()->setAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    
    containerItem->setPositionInPixel(ccp(itemDTO->positionX,itemDTO->positionY));
    containerItem->setGroup(ITEM_GROUP);
    
    containerItem->setLifeTime(itemDTO->lifeTime);
    containerItem->onCreate();
    
    return containerItem;
}

Item* ObjectFactory::createGoldItem(ItemDTO* itemDTO, b2World* world)
{
    GoldItem* item = GoldItem::create();
    
    //sprite
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(itemDTO->imageName.c_str());
    
    item->setPrepareToAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToAppear).c_str()));
    item->setAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_appear).c_str()));
    item->setprepareToDisappearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToDisappear).c_str()));
    
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation = true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, itemDTO->bodyName.c_str());
    item->setSkin(body, sprite);
    
    item->setSpriteAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    item->getSprite()->setAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    
    item->setPositionInPixel(ccp(itemDTO->positionX,itemDTO->positionY));
    item->setGroup(ITEM_GROUP);
    
    item->setLifeTime(itemDTO->lifeTime);
    item->onCreate();
    
    return item;
    
}

Item* ObjectFactory::createBonusItem(ItemDTO* itemDTO, b2World* world)
{
    BonusItem* item = BonusItem::create();
    
    vector<EffectData> listEffectData;
    
    for(int i = 0; i < itemDTO->listAffectID.size(); i++)
    {
        listEffectData.push_back(*EffectFactory::createEffectData(itemDTO->listAffectID[i].c_str()));
    }
    
    item->setListEffectData(listEffectData);
    //sprite
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(itemDTO->imageName.c_str());
    
    item->setPrepareToAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToAppear).c_str()));
    item->setAppearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_appear).c_str()));
    item->setprepareToDisappearAnimation(DataCollector::getInstance()->getAnimationObjectByKey(string(itemDTO->animation + item_prepareToDisappear).c_str()));
    
    //body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation = true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, itemDTO->bodyName.c_str());
    item->setSkin(body, sprite);
    
    item->setSpriteAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    item->getSprite()->setAnchorPoint(sc->anchorPointForShape(itemDTO->bodyName.c_str()));
    
    item->setPositionInPixel(ccp(itemDTO->positionX,itemDTO->positionY));
    item->setGroup(ITEM_GROUP);
    
    item->setLifeTime(itemDTO->lifeTime);
    item->onCreate();
    
    return item;
    
}

ItemCreator* ObjectFactory::createItemCreator(ItemCreatorDTO* itemCreatorDTO)
{
    ItemCreator* itemCreator = ItemCreator::create();
    
    itemCreator->setMax(itemCreatorDTO->max);
    itemCreator->setDelayMax(itemCreatorDTO->delayMax);
    itemCreator->setDelayMin(itemCreatorDTO->delayMin);
    itemCreator->setBeginPosition(ccp(itemCreatorDTO->beginPositionX, itemCreatorDTO->beginPositionY));
    itemCreator->setEndPosition(ccp(itemCreatorDTO->endPositionX, itemCreatorDTO->endPositionY));
    itemCreator->setListItemStructDelayMax(itemCreatorDTO->listItem);
    
    return itemCreator;
}
