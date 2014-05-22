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
#include "DataCollector.h"
#include <queue>

MonsterFactory::MonsterFactory()
{
    this->listMonster = CCArray::create();
    this->listMonster->retain();
    this->listMonsterCreator = CCArray::create();
    this->listMonsterCreator->retain();
    this->isStopped = false;
    this->group = A;
}

MonsterFactory::~MonsterFactory()
{
    stopCreateMonster();
    CC_SAFE_RELEASE_NULL(this->listMonster);
    CC_SAFE_RELEASE_NULL(this->listMonsterCreator);
}

bool MonsterFactory::init()
{
    return true;
}

Monster* MonsterFactory::createMonster(MonsterDTO* monsterDTO, CCPoint position, int laneID, b2World* world)
{
    Monster* monster = Monster::create();

    monster->setOriginCharacterData(monsterDTO->data);
    
    //Create Animation
    string run = monsterDTO->animation;
    string attack = monsterDTO->animation;
    string idle = monsterDTO->animation;
    string fall = monsterDTO->animation;
    string fly = monsterDTO->animation;
    string jump = monsterDTO->animation;
    
    monster->runAnimation = DataCollector::getInstance()->getAnimationObjectByKey(run.append(RUN).c_str());
    monster->attackAnimation = DataCollector::getInstance()->getAnimationObjectByKey(attack.append(ATTACK).c_str());
    monster->jumpAnimation = DataCollector::getInstance()->getAnimationObjectByKey(jump.append(JUMP).c_str());
    monster->idleAnimation = DataCollector::getInstance()->getAnimationObjectByKey(idle.append(IDLE).c_str());
    monster->fallAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fall.append(FALL).c_str());
    monster->flyAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fly.append(FLY).c_str());
    //
    monster->attackAnimation->getAnimation()->setDelayPerUnit(monster->getOriginCharacterData().getAttackSpeed());
    
    //physic data
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, monsterDTO->body.c_str());
    monster->setSpriteAnchorPoint(sc->anchorPointForShape(monsterDTO->body.c_str()));
    monster->getSprite()->setAnchorPoint(sc->anchorPointForShape(monsterDTO->body.c_str()));
    
    monster->setSkin(body, monster->getSprite());
      //monster->getSprite()->setVisible(false);
    //load sensor body
//    b2Body *sensorBody = world->CreateBody(&bodyDef);
//    sc->addFixturesToBody(sensorBody, ((MonsterDTO*)monsterDTO)->sensorBody.c_str());
//    monster->setSensor(sensorBody);
    monster->setSensor(((MonsterDTO*)monsterDTO)->sensorBody.c_str());
    //load skill
    monster->setNormalAttack(SkillFactory::createSkill(monsterDTO->data.getSkill0().c_str(), world, monster, false, SKILL_0_BUTTON));
    //
    monster->setPositionInPixel(position);
    monster->flipDirection(LEFT);
    monster->setGroup(this->group);
    monster->setLaneID(laneID);
    monster->setlistItem(monsterDTO->listItem);
    monster->onCreate();
    monster->setGameObjectView(InfoViewCreator::createMonsterView(monster, NULL));
    return monster;
}

//void MonsterFactory::createMonsters(CharacterDTO* monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster)
//{
//    vector<void*> *prms = new vector<void*>();
//    
//    CCPoint* pos = new CCPoint(position);
//    CharacterDTO* dto = monsterDTO;
//    
//    prms->push_back(dto);
//    prms->push_back(pos);
//    prms->push_back(world);
//    
//    ScheduleManager::getInstance()->scheduleFunction(CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::createMonsterFromSchedule),prms),CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::finishCreateMonsterFromSchedule),prms), timeDelayPerMonster, quantity);
//    
//}

void MonsterFactory::createMonsterList(CCArray* listMonsterDTO, CCPoint position, int laneID, int quantity, float timeDelayPerMonster)
{
    vector<void*> *prms = new vector<void*>();

    CCArray* listDTO = CCArray::createWithCapacity(listMonsterDTO->count());
    listDTO->addObjectsFromArray(listMonsterDTO);
    listDTO->retain();
    
    CCPoint* pos = new CCPoint(position);
    
    int* lID = new int(laneID);
    
    prms->push_back(listDTO);
    prms->push_back(pos);
    prms->push_back(lID);
    prms->push_back(this->holder.worldHolder);
    
    ScheduleManager::getInstance()->scheduleFunction(CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::createMonsterListFromSchedule),prms),CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::finishCreateMonsterListFromSchedule),prms), timeDelayPerMonster, quantity);
}

void MonsterFactory::createMonsterFromSchedule(CCNode* sender, void* data)
{
    
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    MonsterDTO* dto = static_cast<MonsterDTO*>(params->at(0));
    CCPoint *pos = static_cast<CCPoint*>(params->at(1));
    int* laneID = static_cast<int*>(params->at(2));
    b2World *world = static_cast<b2World*>(params->at(3));
    
    addNewMonster(createMonster(dto,*pos,*laneID,world));
    
}


void MonsterFactory::finishCreateMonsterFromSchedule(CCNode* sender, void* data)
{
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    MonsterDTO* dto = static_cast<MonsterDTO*>(params->at(0));
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
        MonsterDTO* dto = (MonsterDTO*)(listMonster->objectAtIndex(0));
        CCPoint *pos = static_cast<CCPoint*>(params->at(1));
        int* laneID = static_cast<int*>(params->at(2));
        b2World *world = static_cast<b2World*>(params->at(3));
        //if (isStopped == false && this->listMonster->count() <= 0)

        {
            addNewMonster(createMonster(dto, *pos, *laneID, world));

        }
        listMonster->removeObjectAtIndex(0);
    }
}

void MonsterFactory::finishCreateMonsterListFromSchedule(CCNode* sender, void* data)
{
 
    std::vector<void*>* params =  static_cast< std::vector<void*>*>(data);
    
    CCArray* listMonster  = static_cast<CCArray*>(params->at(0));
    CCPoint *pos = static_cast<CCPoint*>(params->at(1));
    int* laneID = static_cast<int*>(params->at(2));
    
    //world do not delete
    //b2World *world = static_cast<b2World*>(params->at(2));
    
    listMonster->release();
    delete pos;
    delete laneID;
    
    delete params;
}


void MonsterFactory::addNewMonster(Monster* monster)
{
    GameObjectManager::getInstance()->addGameObject(monster);
    this->listMonster->addObject(monster);
    monster->attach(this);
    monster->attachSpriteTo(this->holder.nodeHolder);
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
    monsterCreator->setLaneID(monsterCreatorDTO->laneID);
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
    this->isStopped = true;
}

void MonsterFactory::startCreateMonster()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterCreator, object)
    {
        MonsterCreator* monsterCreator = static_cast<MonsterCreator*>(object);
        monsterCreator->start();
    }
    this->isStopped = false;
}

void MonsterFactory::update(float dt)
{

}

void MonsterFactory::notifyToDestroy(GameObject* object)
{
    if(this->listMonster->indexOfObject(object) != CC_INVALID_INDEX)
    {
        this->listMonster->removeObject(object);
    }
    
}