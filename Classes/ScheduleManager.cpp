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
CCSequence* ScheduleManager::scheduleForGameObject(GameObject* object, float duration)
{
    CCDelayTime *delayAction = CCDelayTime::create(duration);
    CCCallFuncND *callFuncSelector = CCCallFuncND::create(object, callfuncND_selector(GameObject::excuteScheduledFunction), object);
    CCArray* arr = CCArray::create();
    arr->addObject(delayAction);
    arr->addObject(callFuncSelector);
    
    
    CCSequence* sequence = CCSequence::create(arr);

    this->runAction(sequence);
    return sequence;
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


void ScheduleManager::stopScheduledObjectAction(CCAction* target)
{
    if(target!=NULL)
    {
        this->stopAction(target);
    }

}

void ScheduleManager::scheduleFunction(CCCallFunc* callFunction, CCCallFunc* endFunction, float duration, int repeatTime)
{
    
    
    CCArray* arr1 = CCArray::create();
    arr1->addObject(CCDelayTime::create(duration));
    arr1->addObject(callFunction);
    
    CCArray* arr2 = CCArray::create();
    arr2->addObject(CCRepeat::create(CCSequence::create(arr1), repeatTime));
    arr2->addObject(endFunction);
   
    this->runAction(CCSequence::create(arr2));
    
}

void ScheduleManager::finishScheduleFunction(CCNode* sender, void* data)
{
    CCArray* prms = static_cast<CCArray*>(data);
    prms->release();
}

CCSequence* ScheduleManager::scheduleFuction(CCCallFunc* funcion, float duration)
{
    CCDelayTime *delayAction = CCDelayTime::create(duration);
    CCArray* array = CCArray::create();
    array->addObject(delayAction);
    array->addObject(funcion);
    
    CCSequence* sequence = CCSequence::create(array);
    this->runAction(sequence);
    
    return sequence;
}

CCRepeat* ScheduleManager::scheduleFuctionRepeatly(CCCallFunc* funcion, float duration, int times)
{
    CCDelayTime *delayAction = CCDelayTime::create(duration);
    CCArray* array = CCArray::create();
    array->addObject(delayAction);
    array->addObject(funcion);
    
    CCSequence* sequence = CCSequence::create(array);
    CCRepeat* repeat = CCRepeat::create(sequence, times);
    
    this->runAction(repeat);
    
    return repeat;
}


CCAction* ScheduleManager::scheduleFunctionForever(CCCallFunc* callFunction, CCCallFunc* endFunction, float duration)
{
    CCArray* arr1 = CCArray::create();
    arr1->addObject(CCDelayTime::create(duration));
    arr1->addObject(callFunction);
    
    CCArray* arr2 = CCArray::create();
    arr2->addObject(CCRepeatForever::create(CCSequence::create(arr1)));
    if(endFunction != NULL)
        arr2->addObject(endFunction);
    
    CCRepeatForever* repeatForever = CCRepeatForever::create(CCSequence::create(arr1));
    this->runAction(repeatForever);
    return repeatForever;
}

