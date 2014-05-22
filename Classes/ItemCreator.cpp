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
    this->listItem = CCArray::create();
    this->listItem->retain();
    this->delayAction = NULL;
    this->isStopped = false;
}

ItemCreator::~ItemCreator()
{
    this->listItem->release();
}

bool ItemCreator::init()
{
    return true;
}

void ItemCreator::start()
{
    this->isStopped = false;
    CCCallFunc* createFunction = CCCallFunc::create(this, callfunc_selector(ItemCreator::createItem));
    
    this->delayAction = ScheduleManager::getInstance()->scheduleFunction(createFunction, NULL, this->delayMin + CCRANDOM_0_1()*this->delayMax, 1);
    this->delayAction->retain();
}

void ItemCreator::stop()
{
    this->isStopped = true;
    if(this->delayAction != NULL && this->delayAction->isDone() == false)
    {
        ScheduleManager::getInstance()->stopAction(this->delayAction);
        this->delayAction->release();
        this->delayAction = NULL;
    }
}

void ItemCreator::createItem()
{
    if(this->isStopped == false)
    {
        vector<ItemStruct> listItem = Util::randomItemInList(this->listItemStruct, 1);
        
        for (int i = 0; i < listItem.size(); i++)
        {
            CCPoint createPosition = this->beginPosition + ccp(CCRANDOM_0_1()* (this->endPosition.x - this->beginPosition.x), CCRANDOM_0_1()*(this->endPosition.y - this->beginPosition.y));
            
            Item* item = ItemFactory::getInstance()->createItem(listItem[i].itemID.c_str(), createPosition);
            this->listItem->addObject(item);
            item->attach(this);
        }
        if(this->listItem->count() < this->max)
        {
            start();
        }
    }
}

void ItemCreator::notifyToDestroy(GameObject* object)
{
    if(this->listItem->count() == this->max && isStopped == false)
    {
        start();
    }
    
    if(this->listItem->indexOfObject(object) != CC_INVALID_INDEX)
    {
        this->listItem->removeObject(object);
    }
    
}
