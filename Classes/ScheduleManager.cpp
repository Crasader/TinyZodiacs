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