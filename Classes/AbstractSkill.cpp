//
//  AbstractSkill.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#include "AbstractSkill.h"

#include "ScheduleManager.h"
#include "EffectData.h"
#include "Character.h"

AbstractSkill::AbstractSkill(GameObject* holder, SkillData data)
{
    this->isDisable = false;
    this->excuteAction = NULL;
    this->stopAction = NULL;
    this->coolDownAction = NULL;
    this->holderButton = NULL;
    this->isExcutable = true;


    if(holder != NULL)
    {
        this->holder = holder;
    //    this->holder->retain();
    }
    this->autorelease();
}

AbstractSkill::~AbstractSkill()
{
    if(this->holder != NULL)
    {
     //   this->holder->release();
    }
}

void AbstractSkill::onCreate()
{
    
}

void AbstractSkill::destroy()
{
    this->isDisable = true;
    stopAllAction();
}

void AbstractSkill::stopAllAction()
{
    if(excuteAction != NULL)
    {
        if(excuteAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(excuteAction);
        }
        excuteAction->release();
    }
    if(stopAction != NULL)
    {
        if(stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopScheduledObjectAction(stopAction);
        }
        stopAction->release();
    }
    if(coolDownAction != NULL)
    {
        if(coolDownAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(coolDownAction);
        }
        coolDownAction->release();
    }
}

void AbstractSkill::calculateSkillData(SkillData* data, GameObject* character)
{
    //Calculate enemy effect list
    vector<EffectData> listEffect = data->getListEnemyEffect();
    for(int i=0 ; i<listEffect.size() ; i++)
    {
        EffectData effectData = data->getListEnemyEffect()[i];
        effectData.setHealth(effectData.getHealth()-((Character*)character)->getcharacterData().getAttack());
        listEffect[i] = effectData;
//        CCLOG("%d",data->getListEnemyEffect()[i].getHealth());
    }
    data->setListEnemyEffect(listEffect);
}
