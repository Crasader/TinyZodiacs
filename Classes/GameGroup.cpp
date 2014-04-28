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

GameGroup::GameGroup()
{
    this->monsterFactory = MonsterFactory::create();
    this->monsterFactory->retain();
    this->listTower = CCArray::create();
    this->listTower->retain();
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
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->monsterFactory->getListMonster(), object)
    {
        Monster* monster = static_cast<Monster*>(object);
        if(monster != NULL)
        {
            monster->update(dt);
        }
    }
    
    object = NULL;
    CCARRAY_FOREACH(this->listTower, object)
    {
        Tower* tower = dynamic_cast<Tower*>(object);
        if(tower != NULL)
        {
            tower->update(dt);
        }
    }
    
    
}

void GameGroup::joinGame(b2World* world, Map* map)
{
    //CHARACTER
    this->character = ObjectFactory::getSharedManager()->createCharacter("character_cat.xml", world, true);
    this->character->setPositionInPixel(ccp(1500,1200));
    this->character->setGroup(A);
    
    this->character->retain();
    
    map->addChild(character->getSprite(), CHARACTER_LAYER);
    
    
    //MONSTER
    this->monsterFactory->setHolder(map);
    
    CharacterDTO dto2 = CharacterFactory::loadXMLFile("character_cat.xml");
    
    this->monsterFactory->createMonsters(dto2,ccp(3000,400),50,2, world);
    
    CharacterDTO dto = CharacterFactory::loadXMLFile("character_monkey.xml");
    
    //towers
    
    CCArray* arrTower = CCArray::create();
    
    CCObject* object = NULL;
    
    CCARRAY_FOREACH(map->getListTowerDTO(), object)
    {
        
        Tower* tower = dynamic_cast<Tower*>(object);
        if(tower != NULL)
        {
            arrTower->addObject(tower);
        }
        
    }
    
    
   // createTowers(<#cocos2d::CCArray *towerDTO#>, <#b2World *world#>)
    
    
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

