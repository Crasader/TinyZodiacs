//
//  Wave.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/21/14.
//
//

#include "Wave.h"

Wave::Wave()
{
    this->monsterFactory = MonsterFactory::create();
    this->monsterFactory->retain();
    this->monsterFactory->setGroup(B);
    
    this->listMonsterFactory = CCArray::create();
    this->listMonsterFactory->retain();
    this->listItemCreator = CCArray::create();
    this->listItemCreator->retain();
}

Wave::~Wave()
{
    this->monsterFactory->release();
    this->listMonsterFactory->release();
    this->listItemCreator->release();
}

bool Wave::init()
{
    return true;
}

void Wave::setHolder(GameHolder holder)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterFactory, object)
    {
        MonsterFactory* monsterFactory = static_cast<MonsterFactory*>(object);
        monsterFactory->setHolder(holder);
    }
}

void Wave::addMonsterFactory(MonsterFactory* monsterFactory)
{
    if(monsterFactory != NULL)
    {
        this->listMonsterFactory->addObject(monsterFactory);
    }
}

void Wave::addItemCreator(ItemCreator* itemCreator)
{
    if(itemCreator != NULL)
    {
        this->listItemCreator->addObject(itemCreator);
    }
}

void Wave::startCreateMonster()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterFactory, object)
    {
        MonsterFactory* monsterFactory = static_cast<MonsterFactory*>(object);
        monsterFactory->setHolder(GameManager::getInstance()->getGameplayHolder());
        monsterFactory->startCreateMonster();
    }
}

void Wave::startCreateItem()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listItemCreator, object)
    {
        ItemCreator* itemCreator = static_cast<ItemCreator*>(object);
        itemCreator->start();
    }
}

void Wave::stopCreateMonster()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterFactory, object)
    {
        MonsterFactory* monsterFactory = static_cast<MonsterFactory*>(object);
        monsterFactory->stopCreateMonster();
    }
}

void Wave::stopCreateItem()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listItemCreator, object)
    {
        ItemCreator* itemCreator = static_cast<ItemCreator*>(object);
        itemCreator->stop();
    }
}

void Wave::start()
{
    startCreateMonster();
    startCreateItem();
}

void Wave::stop()
{
    stopCreateMonster();
    stopCreateItem();
}

int Wave::getMonsterCount()
{
    int count = 0;
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listMonsterFactory, object)
    {
        MonsterFactory* monsterFactory = static_cast<MonsterFactory*>(object);
        count += monsterFactory->getListMonster()->count();
    }
    return count;
}

