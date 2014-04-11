//
//  ScheduleManager.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/26/14.
//
//

#include "ScheduleManager.h"
static ScheduleManager* instance;

ScheduleManager::ScheduleManager()
{
    
}
ScheduleManager::~ScheduleManager()
{
    
}
void ScheduleManager::scheduleForGameObject(GameObject* object, float duration)
{
    CCDelayTime *delayAction = CCDelayTime::create(duration);
    CCCallFuncND *callFuncSelector = CCCallFuncND::create(object, callfuncND_selector(GameObject::excuteScheduledFunction), object);
    this->runAction(CCSequence::create(delayAction,callFuncSelector));
}
void ScheduleManager::scheduleForSkill(AbstractSkill* object, float duration, int fuctionCall)
{
    CCCallFunc *callFuncSelector;
    if(fuctionCall == FUCTION_EXCUTE)
    {
        callFuncSelector = CCCallFunc::create(object, callfunc_selector(AbstractSkill::excuteImmediately));
    }
    else if (fuctionCall == FUCTION_STOP)
    {
        callFuncSelector = CCCallFunc::create(object, callfunc_selector(AbstractSkill::stopImmediately));
    }
    else if (fuctionCall == FUCTION_SET_EXCUTABLE)
    {
        callFuncSelector = CCCallFunc::create(object, callfunc_selector(AbstractSkill::setExcuteAble));
    }
    CCArray* array = CCArray::create();
    if(duration>0)
    {
        CCDelayTime *delayAction = CCDelayTime::create(duration);
        array->addObject(delayAction);
    }
    array->addObject(callFuncSelector);
    CCSequence* sequence = CCSequence::create(array);
    this->runAction(sequence);
}
ScheduleManager* ScheduleManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new ScheduleManager();
    }
    return instance;
}
void ScheduleManager::release()
{
    delete  instance;
}