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
#include "SoundManager.h"

AbstractSkill::AbstractSkill(GameObject* holder, SkillData data)
{
    this->isDisable = false;
    this->excuteAction = NULL;
    this->stopAction = NULL;
    this->coolDownAction = NULL;
    this->isExcutable = true;
    this->skillButtonID = UNKNOWN;
    
    if(holder != NULL)
    {
        this->holder = holder;
    }
    this->autorelease();
}

AbstractSkill::~AbstractSkill()
{
    this->holder = NULL;
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
            ScheduleManager::getInstance()->stopAction(excuteAction);
        }
        excuteAction->release();
        excuteAction = NULL;
    }
    if(stopAction != NULL)
    {
        if(stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(stopAction);
        }
        stopAction->release();
        stopAction = NULL;
    }
    if(coolDownAction != NULL)
    {
        if(coolDownAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(coolDownAction);
        }
        
        coolDownAction->release();
        coolDownAction = NULL;
    }
}

void AbstractSkill::calculateSkillData(SkillData* data, CharacterData characterData)
{
    //Calculate enemy effect list
    vector<EffectData> listEffect = data->getListEnemyEffect();
    for(int i=0 ; i<listEffect.size() ; i++)
    {
        EffectData effectData = data->getListEnemyEffect()[i];
        effectData.setHealth(effectData.getHealth()-characterData.getAttack());
        listEffect[i] = effectData;
        //        CCLOG("%d",data->getListEnemyEffect()[i].getHealth());
    }
    data->setListEnemyEffect(listEffect);
}

void AbstractSkill::excute()
{
    
}

void AbstractSkill::stop()
{
    
}

void AbstractSkill::excuteImmediately()
{
    
}

void AbstractSkill::stopImmediately()
{
    
}

void AbstractSkill::playSFX(const char* sfxName)
{
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sfxName);
    if(this->holder->shouldHaveSound())
    {
        SoundManager::playSoundEffect(sfxName, false);
    }
}

void AbstractSkill::stopSFX(unsigned int sfxid)
{
    SoundManager::stopSoundEffect(sfxid);
}

void AbstractSkill::playSoundByState(SkillSound soundState, SkillSoundData data)
{
    switch (soundState) {
        case EXCUTE_SOUND:
        {
            playSFX(data.getExcuteSoundStr().c_str());
        }
            break;
        case STOP_SOUND:
        {
            playSFX(data.getStopSoundStr().c_str());
        }
            break;
        case SKILL_HIT_SOUND:
        {
            playSFX(data.getHitSoundStr().c_str());
        }
            break;
        default:
            break;
    }
}