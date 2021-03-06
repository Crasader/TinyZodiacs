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
#include "WaveDTO.h"
#include "RuleManager.h"

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
    this->monsterFactory->release();
    this->listTower->release();
}

bool GameGroup::init()
{
    return true;
}

void GameGroup::update(float dt)
{
//    this->character->update(dt);
}

void GameGroup::joinGame(Group group, b2World* world, Map* map)
{
    
    this->group = group;
    this->monsterFactory->setGroup(this->group);
    //CHARACTER
//    this->character = ObjectFactory::createHero(DataCollector::getInstance()->getHeroDTOByKey("cat"), world, false);
//    this->character->setPositionInPixel(ccp(2500,500));
//    this->character->setGroup(this->group);
//    
//    this->character->retain();
//    this->character->setGameObjectView(InfoViewCreator::createHeroView(this->character, NULL));

    
    //MONSTER
    
    GameHolder holder;
    holder.worldHolder = world;
    holder.nodeHolder = map;
    
    
    this->monsterFactory->setHolder(holder);
    
    //towers
    
    CCArray* arrTowerStruct = CCArray::create();
    
    CCObject* object = NULL;
    
    CCARRAY_FOREACH(map->getMapDTO()->listTowerStructDTO, object)
    {
        TowerStructDTO* towerStructDTO = dynamic_cast<TowerStructDTO*>(object);
        if(towerStructDTO != NULL)
        {
            if(towerStructDTO->group == this->group)
            {
                arrTowerStruct->addObject(towerStructDTO);
            }
        }
    }
    
    //monster factory
    object = NULL;
    CCARRAY_FOREACH(map->getMapDTO()->listMonsterFactoryDTO, object)
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
    
   // this->monsterFactory->startCreateMonster();
    
    
    
    createTowers(arrTowerStruct, world);
    
    attachSpriteToMap(map);
    
//    if(group == B)
//    {
//        ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this->character);
//    }

    
}

Character* GameGroup::getFollowingCharacter()
{
    //  Character* character = static_cast<Character*>(this->monsterFactory->getListMonster()->objectAtIndex(0));
//    Character* character = static_cast<Character*>(this->character);
    return NULL;
}

Character* GameGroup::getCharacterOfPlayer()
{
    return NULL;
}

void GameGroup::createTowers(CCArray* listTowerStructDTO, b2World* world)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(listTowerStructDTO, object)
    {
        TowerStructDTO* towerDTO = static_cast<TowerStructDTO*>(object);
        Tower* tower = ObjectFactory::createTower(towerDTO, world);
        this->listTower->addObject(tower);
        tower->attach(this);
        GameObjectManager::getInstance()->addGameObject(tower);
        tower->setGameObjectView(InfoViewCreator::createTowerView(tower, NULL));
        tower->attachSpriteTo(GameManager::getInstance()->getGameplayHolder().nodeHolder);
    }
}

void GameGroup::attachSpriteToMap(Map* map)
{
//    character->attachSpriteTo(map);
    
}

void GameGroup::test()
{
    //  EffectManager::getInstance()->clean();
}

void GameGroup::notifyToDestroy(GameObject* object)
{
    if(this->listTower->indexOfObject(object) != CC_INVALID_INDEX)
    {
        this->listTower->removeObject(object);
    }
}

bool GameGroup::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    return true;
}

bool GameGroup::removeSubController(Controller* controller)
{
    Controller::removeSubController(controller);
    return true;
}
