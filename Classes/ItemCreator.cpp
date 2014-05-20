//
//  ItemCreator.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#include "ItemCreator.h"

ItemCreator::ItemCreator()
{
    
}

ItemCreator::~ItemCreator()
{
    
}

bool ItemCreator::init()
{
    return true;
}

void ItemCreator::start()
{
//    CCDelayTime* delayTime = CCDelayTime::create(this->delayMin + CCRANDOM_0_1()*this->delayMax);
    CCCallFunc* createFunction = CCCallFunc::create(this, callfunc_selector(ItemCreator::createItem));
//    
//    CCSequence* seq = CCSequence::create(delayTime,createFunction,NULL);
//    
    ScheduleManager::getInstance()->scheduleFunction(createFunction, NULL, this->delayMin + CCRANDOM_0_1()*this->delayMax, 1);
}

void ItemCreator::end()
{
    
}

void ItemCreator::createItem()
{
    CCPoint createPosition = this->beginPosition + ccp(CCRANDOM_0_1()* (this->endPosition.x - this->beginPosition.x), CCRANDOM_0_1()*(this->endPosition.y - this->beginPosition.y));
    
    ItemFactory::getInstance()->createItem(this->listItemStruct[0].itemID.c_str(), createPosition);
    start();
}