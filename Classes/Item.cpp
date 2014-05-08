//
//  Item.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "Item.h"

Item::Item()
{
    this->lifeTime = 0;
}

Item::~Item()
{
    
}

bool Item::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    
    return true;
}

void Item::destroy()
{
    if(!this->lifeTimeAction->isDone())
    {
        ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
    }
    this->lifeTimeAction->release();
    
    ItemFactory::getInstance()->destroyItem(this);
}

void Item::startSchedule()
{
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::destroy));
    this->lifeTimeAction = ScheduleManager::getInstance()->scheduleFunction(destroyFunction, NULL, this->lifeTime, 1);
    this->lifeTimeAction->retain();
}

