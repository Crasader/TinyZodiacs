//
//  GameGroup.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/28/14.
//
//

#include "GameGroup.h"
#include "ObjectFactory.h"
#include "LayerIndexConstants.h"
#include "EffectManager.h"

GameGroup::GameGroup()
{
    this->monsterFactory = MonsterFactory::create();
    this->monsterFactory->retain();
    this->listTower = CCArray::create();
    this->listTower->retain();
    this->group = A;
}

GameGroup::~GameGroup()
{
    CC_SAFE_RELEASE_NULL(this->monsterFactory);
    CC_SAFE_RELEASE_NULL(this->listTower);
}

bool GameGroup::init()
{
    return true;
}

void GameGroup::update(float dt)
{
    this->character->update(dt);
    
    CCArray* listMonsterRemoved = CCArray::create();
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->monsterFactory->getListMonster(), object)
    {
        Monster* monster = static_cast<Monster*>(object);
        monster->update(dt);
        if(monster->isDead())
        {
            listMonsterRemoved->addObject(monster);
        }
    }
    //remove monster
    object = NULL;
    CCARRAY_FOREACH(listMonsterRemoved, object)
    {
        Monster* monster = static_cast<Monster*>(object);
        this->monsterFactory->getListMonster()->removeObject(monster);
    }
    listMonsterRemoved->removeAllObjects();
    
    //
    object = NULL;
    CCARRAY_FOREACH(this->listTower, object)
    {
        Tower* tower = dynamic_cast<Tower*>(object);
        if(tower != NULL)
        {
            tower->update(dt);
        }
    }
    
    this->monsterFactory->update(dt);
    
}

void GameGroup::joinGame(Group group, b2World* world, Map* map)
{
    this->group = group;
    this->monsterFactory->setGroup(this->group);
    //CHARACTER
    
    this->character = ObjectFactory::getSharedManager()->createHero(DataCollector::getInstance()->getHeroDTOByKey("cat"), world, true);
    this->character->setPositionInPixel(ccp(1500,1200));
    this->character->setGroup(this->group);
    
    this->character->retain();
    
    //MONSTER
    this->monsterFactory->setHolder(map);
    this->monsterFactory->setWorld(world);
    
    //towers
    
    CCArray* arrTower = CCArray::create();
    
    CCObject* object = NULL;
    
    CCARRAY_FOREACH(map->getListTowerDTO(), object)
    {
        TowerDTO* towerDTO = dynamic_cast<TowerDTO*>(object);
        if(towerDTO != NULL)
        {
            if(strcasecmp(towerDTO->group.c_str(), "A") == 0 && this->group == A)
            {
                arrTower->addObject(towerDTO);
            }
            else if(strcasecmp(towerDTO->group.c_str(), "B") == 0 && this->group == B)
            {
                arrTower->addObject(towerDTO);
            }
            else
            {
                
            }
        }
    }
    
    
    //monster factory
    object = NULL;
    CCARRAY_FOREACH(map->getListMonsterFactoryDTO(), object)
    {
        MonsterFactoryDTO* monsterFactoryDTO = dynamic_cast<MonsterFactoryDTO*>(object);
        if(monsterFactoryDTO != NULL)
        {
            if(monsterFactoryDTO->group == this->group)
            {
                CCObject* object1 = NULL;
                CCARRAY_FOREACH(monsterFactoryDTO->listMonsterCreatorDTO, object1)
                {
                    MonsterCreatorDTO* monsterCreatorDTO = dynamic_cast<MonsterCreatorDTO*>(object1);
                    this->monsterFactory->registerMonsterCreator(monsterCreatorDTO, world);
                }
            }
        }
    }
    
    this->monsterFactory->startCreateMonster();
    
    
    createTowers(arrTower, world);
    
    attachSpriteToMap(map);
    
}

void GameGroup::BeginContact(b2Contact* contact)
{
    //character
    this->character->BeginContact(contact);
    
    //monster
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->monsterFactory->getListMonster(), object)
    {
        Monster* monster = static_cast<Monster*>(object);
        if(monster != NULL)
        {
            monster->BeginContact(contact);
        }
    }
    
    //towers
    object = NULL;
    CCARRAY_FOREACH(this->listTower, object)
    {
        Tower* tower = dynamic_cast<Tower*>(object);
        if(tower != NULL)
        {
            tower->BeginContact(contact);
        }
    }
    
}

void GameGroup::EndContact(b2Contact* contact)
{
    //character
    this->character->EndContact(contact);
    
    //monsters
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->monsterFactory->getListMonster(), object)
    {
        Monster* monster = static_cast<Monster*>(object);
        if(monster != NULL)
        {
            monster->EndContact(contact);
        }
    }
    
    //towers
    object = NULL;
    CCARRAY_FOREACH(this->listTower, object)
    {
        Tower* tower = dynamic_cast<Tower*>(object);
        if(tower != NULL)
        {
            tower->EndContact(contact);
        }
    }
    
}

Character* GameGroup::getFollowingCharacter()
{
    //  Character* character = static_cast<Character*>(this->monsterFactory->getListMonster()->objectAtIndex(0));
    Character* character = static_cast<Character*>(this->character);
    return character;
}

Character* GameGroup::getCharacterOfPlayer()
{
    return this->character;
}

void GameGroup::createTowers(CCArray* towerDTO, b2World* world)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(towerDTO, object)
    {
        TowerDTO* towerDTO = static_cast<TowerDTO*>(object);
        this->listTower->addObject(ObjectFactory::getSharedManager()->createTower(towerDTO, world));
    }
}

void GameGroup::attachSpriteToMap(Map* map)
{
    map->addChild(character->getSprite(), CHARACTER_LAYER);
    
    //towers
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listTower, object)
    {
        Tower* tower = static_cast<Tower*>(object);
        map->addChild(tower->getSprite(), UNDER_CHARACTER_LAYER);
    }
    
}

void GameGroup::test()
{
  //  EffectManager::getInstance()->clean();
}

