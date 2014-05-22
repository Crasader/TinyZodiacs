//
//  MonsterCreator.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/30/14.
//
//

#include "MonsterCreator.h"
#include "DataCollector.h"

MonsterCreator::MonsterCreator()
{
    this->delay = 0;
    this->delayPerUnit = 0;
    this->monsterFactory = NULL;
    this->actionCreateMonster = NULL;
}

MonsterCreator::~MonsterCreator()
{
    this->listMonsterID.clear();
}

bool MonsterCreator::init()
{
    return true;
}

void MonsterCreator::createMonster()
{
    CCArray* temp = CCArray::create();
    for(int i = 0; i < this->listMonsterID.size(); i++)
    {
        temp->addObject(DataCollector::getInstance()->getMonsterDTOByKey(this->listMonsterID[i].c_str()));
    }
    this->monsterFactory->createMonsterList(temp, ccp(this->position.x, this->position.y), this->laneID, temp->count(), this->delayPerUnit);
}

void MonsterCreator::start()
{
   this->actionCreateMonster = ScheduleManager::getInstance()->scheduleFunctionForever(CCCallFunc::create(this,callfunc_selector(MonsterCreator::createMonster)), NULL, this->delay);
}

void MonsterCreator::stop()
{
    if(this->actionCreateMonster != NULL)
    {
        ScheduleManager::getInstance()->stopAction(this->actionCreateMonster);
    }
}
