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
#include "PhysicBodyManager.h"
#include "LayerIndexConstants.h"

static MonsterFactory* sharedFactory = NULL;



MonsterFactory::MonsterFactory()
{
    this->listMonster = CCArray::create();
    this->listMonster->retain();
}

MonsterFactory::~MonsterFactory()
{
    delete sharedFactory;
    CC_SAFE_RELEASE_NULL(this->listMonster);
}

MonsterFactory* MonsterFactory::getSharedFactory()
{
    if (!sharedFactory)
    {
        sharedFactory = new MonsterFactory();
    }
    return sharedFactory;
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
    
    monster->setGroup(GROUP_HERO_A);
    monster->flipDirection(LEFT);
    monster->setLaneID(2);
    
    return monster;
}

void MonsterFactory::createMonsters(CharacterDTO monsterDTO, CCPoint position, int quantity, float timeDelayPerMonster, b2World* world)
{
    vector<void*> *prms = new vector<void*>();
    
    CCPoint* pos = new CCPoint(position);
    CharacterDTO* dto = new CharacterDTO(monsterDTO);
    
    prms->push_back(dto);
    prms->push_back(pos);
    prms->push_back(world);
    
    ScheduleManager::getInstance()->scheduleFunction(CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::createMonsterFromSchedule),prms),CCCallFuncND::create((CCObject*)this, callfuncND_selector(MonsterFactory::finishCreateMonsterFromSchedule),prms), timeDelayPerMonster, quantity);
    
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

void MonsterFactory::addNewMonster(Monster* monster)
{
    this->listMonster->addObject(monster);
    this->holder->addChild(monster->getSprite(),CHARACTER_LAYER);
}
void MonsterFactory::removeMonster(Monster* monster)
{
    Monster* mons =  (Monster*)this->listMonster->objectAtIndex(0);
    this->listMonster->removeObject(mons);
}

void MonsterFactory::update(float dt)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonster, object)
    {
        
        Monster* monster = static_cast<Monster*>(object);
        if(monster!=NULL)
        {
            monster->update(dt);
        
        }
    }
}
