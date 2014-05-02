//
//  MonsterFactory.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/15/14.
//
//

#include "MonsterFactory.h"
#include "ScheduleManager.h"
#include "ParameterObject.h"
#include "GameObjectManager.h"
#include "LayerIndexConstants.h"
#include <queue>

MonsterFactory::MonsterFactory()
{
    this->listMonster = CCArray::create();
    this->listMonster->retain();
    this->listMonsterCreator = CCArray::create();
    this->listMonsterCreator->retain();
    this->listMonsterRemoved = CCArray::create();
    this->listMonsterRemoved->retain();
    this->group = A;
}

MonsterFactory::~MonsterFactory()
{
    stopCreateMonster();
    CC_SAFE_RELEASE_NULL(this->listMonster);
    CC_SAFE_RELEASE_NULL(this->listMonsterRemoved);
    CC_SAFE_RELEASE_NULL(this->listMonsterCreator);
}

bool MonsterFactory::init()
{
    return true;
}

Monster* MonsterFactory::createMonster(CharacterDTO monsterDTO, CCPoint position, b2World* world)
{
    Monster* monster = Monster::create();
    // monster->retain();
    
    monster->setOriginCharacterData(monsterDTO.data);
    
    //Create Animation
    string run = monsterDTO.animation;
    string attack = monsterDTO.animation;
    string idle = monsterDTO.animation;
    string fall = monsterDTO.animation;
    string fly = monsterDTO.animation;
    string jump = monsterDTO.animation;
    
    monster->runAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(run.append(RUN).c_str());
    monster->attackAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(attack.append(ATTACK).c_str());
    monster->jumpAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(jump.append(JUMP).c_str());
    monster->idleAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(idle.append(IDLE).c_str());
    monster->fallAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fall.append(FALL).c_str());
    monster->flyAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fly.append(FLY).c_str());
    //
    monster->attackAnimation->getAnimation()->setDelayPerUnit(monster->getOriginCharacterData().getAttackSpeed());
    
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    bodyDef.userData = monster;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, monsterDTO.body.c_str());
    monster->setSpriteAnchorPoint(sc->anchorPointForShape(monsterDTO.body.c_str()));
    monster->getSprite()->setAnchorPoint(sc->anchorPointForShape(monsterDTO.body.c_str()));
    
    monster->setSkin(body, monster->getSprite());
    //  monster->getSprite()->setVisible(false);
    
    //
    monster->setPositionInPixel(position);
    monster->setGroup(this->group);
    monster->flipDirection(LEFT);
    monster->setLaneID(3);
       
    return monster;
}

void MonsterFactory::createMonsters(CharacterDTO monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster)
{
    vector<void*> *prms = new vector<void*>();
    
    CCPoint* pos = new CCPoint(position);
    CharacterDTO* dto = new CharacterDTO(monsterDTO);
    
    prms->push_back(dto);
    prms->push_back(pos);
    prms->push_back(world);
    
    ScheduleManager::getInstance()->scheduleFunction(CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::createMonsterFromSchedule),prms),CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::finishCreateMonsterFromSchedule),prms), timeDelayPerMonster, quantity);
    
}

void MonsterFactory::createMonsterList(CCArray* listMonsterDTO, CCPoint position, int quantity, float timeDelayPerMonster)
{
    vector<void*> *prms = new vector<void*>();
    
    CCPoint* pos = new CCPoint(position);
    
    CCArray* listDTO = CCArray::createWithCapacity(listMonsterDTO->count());
    listDTO->addObjectsFromArray(listMonsterDTO);
    listDTO->retain();
    
    prms->push_back(listDTO);
    prms->push_back(pos);
    prms->push_back(this->world);
    
    ScheduleManager::getInstance()->scheduleFunction(CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::createMonsterListFromSchedule),prms),CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::finishCreateMonsterListFromSchedule),prms), timeDelayPerMonster, quantity);
}

void MonsterFactory::createMonsterFromSchedule(CCNode* sender, void* data)
{
    
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    CharacterDTO* dto = static_cast<CharacterDTO*>(params->at(0));
    CCPoint *pos = static_cast<CCPoint*>(params->at(1));
    b2World *world = static_cast<b2World*>(params->at(2));
    
    addNewMonster(createMonster(*dto,*pos,world));
    
}


void MonsterFactory::finishCreateMonsterFromSchedule(CCNode* sender, void* data)
{
    CCLOG("des");
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    CharacterDTO* dto = static_cast<CharacterDTO*>(params->at(0));
    CCPoint *pos = static_cast<CCPoint*>(params->at(1));
    
    //world do not delete
    //b2World *world = static_cast<b2World*>(params->at(2));
    
    
    delete dto;
    delete pos;
    
    delete params;
}

void MonsterFactory::createMonsterListFromSchedule(CCNode* sender, void* data)
{
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    CCArray* listMonster  = static_cast<CCArray*>(params->at(0));
    
    if(listMonster->count() > 0)
    {
        CharacterDTO* dto = (CharacterDTO*)(listMonster->objectAtIndex(0));
        CCPoint *pos = static_cast<CCPoint*>(params->at(1));
        b2World *world = static_cast<b2World*>(params->at(2));
        addNewMonster(createMonster(*dto,*pos,world));
        listMonster->removeObjectAtIndex(0);
    }
}

void MonsterFactory::finishCreateMonsterListFromSchedule(CCNode* sender, void* data)
{
    CCLOG("des list");
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    CCArray* listMonster  = static_cast<CCArray*>(params->at(0));
    CCPoint *pos = static_cast<CCPoint*>(params->at(1));
    
    //world do not delete
    //b2World *world = static_cast<b2World*>(params->at(2));
    
    listMonster->release();
    delete pos;
    
    delete params;
}


void MonsterFactory::addNewMonster(Monster* monster)
{
    this->listMonster->addObject(monster);
    this->holder->addChild(monster->getSprite(),CHARACTER_LAYER);
}
void MonsterFactory::removeMonster(Monster* monster)
{
    this->listMonster->removeObject(monster);
}

void MonsterFactory::registerMonsterCreator(MonsterCreatorDTO* monsterCreatorDTO, b2World* world)
{
    MonsterCreator* monsterCreator = MonsterCreator::create();
    monsterCreator->setDelay(monsterCreatorDTO->delay);
    monsterCreator->setDelayPerUnit(monsterCreatorDTO->delayPerUnit);
    monsterCreator->setListMonsterID(monsterCreatorDTO->listMonsterID);
    monsterCreator->setPosition(ccp(monsterCreatorDTO->positionX,monsterCreatorDTO->positionY));
    monsterCreator->setMonsterFactory(this);
    
    this->listMonsterCreator->addObject(monsterCreator);
}

void MonsterFactory::stopCreateMonster()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterCreator, object)
    {
        MonsterCreator* monsterCreator = static_cast<MonsterCreator*>(object);
        monsterCreator->stop();
    }
}

void MonsterFactory::startCreateMonster()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterCreator, object)
    {
        MonsterCreator* monsterCreator = static_cast<MonsterCreator*>(object);
        monsterCreator->start();
    }
}

void MonsterFactory::update(float dt)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterRemoved, object)
    {
        Monster* monster = static_cast<Monster*>(object);
        this->getListMonster()->removeObject(monster);
    }
    this->listMonsterRemoved->removeAllObjects();
}