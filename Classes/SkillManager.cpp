//
//  SkillManager.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 7/3/14.
//
//

#include "SkillManager.h"

SkillManager* mInstance = NULL;

SkillManager::SkillManager()
{
    this->listStopSkill = CCArray::create();
    this->listStopSkill->retain();
}

SkillManager::~SkillManager()
{
    this->listStopSkill->removeAllObjects();
    this->listStopSkill->release();
}

bool SkillManager::init()
{
    return true;
}

SkillManager* SkillManager::getInstance()
{
    if(mInstance == NULL)
    {
        mInstance = SkillManager::create();
        mInstance->retain();
    }
    return mInstance;
}

void SkillManager::addSkillToBeStop(AbstractSkill* skill)
{
    this->listStopSkill->addObject(skill);
}

void SkillManager::update(float dt)
{
    CCObject* obj;
    CCARRAY_FOREACH(this->listStopSkill, obj)
    {
        ((AbstractSkill*)obj)->stopImmediately();
    }
    this->listStopSkill->removeAllObjects();
}

void SkillManager::destroy()
{
    mInstance->release();
    mInstance = NULL;
}