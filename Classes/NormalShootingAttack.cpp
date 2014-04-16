//
//  NormalShootingAttack.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/19/14.
//
//

#include "NormalShootingAttack.h"
#include "Util.h"
#include "GB2ShapeCache-x.h"
#include "ScheduleManager.h"


NormalShootingAttack::~NormalShootingAttack()
{
    projectTileList->release();
}

NormalShootingAttack::NormalShootingAttack(GameObject* holder, NormalShootingSkillData data)
{
    if(holder != NULL)
    {
        this->holder = holder;
        this->data = data;
        this->isExcutable = true;
        this->holderButton = NULL;
        
        projectTileList = CCArray::create();
        projectTileList->retain();
    }
}


void NormalShootingAttack::excute()
{
    if(this->getIsExcutable())
    {
        ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getDelay(), FUCTION_EXCUTE);
        if(this->data.getCoolDown() > 0)
        {
            ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getCoolDown(), FUCTION_SET_EXCUTABLE);
            this->isExcutable = false;
            if(this-> holderButton != NULL)
            {
                this->holderButton->changeState(DISABLE);
            }
        }
        else
        {
            this->AbstractSkill::excuteImmediately();
        }
    }
}

void NormalShootingAttack::stop()
{
    
}

void NormalShootingAttack::update(float dt)
{
    for(unsigned int i=0; i< projectTileList->count() ; i++)
    {
        if(((NormalProjectile*)projectTileList->objectAtIndex(i)) != NULL)
        {
            ((NormalProjectile*)projectTileList->objectAtIndex(i))->update(dt);
        }
    }
    
    if(this->holderButton != NULL)
    {
        if(this->isExcutable)
        {
            //            this->holderButton->changeState(ENABLE);
        }
        else
        {
            this->holderButton->changeState(DISABLE);
        }
    }
}

void NormalShootingAttack::BeginContact(b2Contact *contact)
{
    AbstractSkill::BeginContact(contact);
}

void NormalShootingAttack::EndContact(b2Contact *contact)
{
    AbstractSkill::EndContact(contact);
}

void NormalShootingAttack::setGroup(int group)
{
    this->group = group;
}

void NormalShootingAttack::excuteImmediately()
{
    if(holder != NULL)
    {
        NormalProjectile* proj = new NormalProjectile(this->data, this->holder, this->projectTileList);
        proj->setGroup(GROUP_SKILL_DEFAULT);
        //
        projectTileList->addObject(proj);
    }

}

void NormalShootingAttack::stopImmediately()
{
    
}

void NormalShootingAttack::setExcuteAble()
{
    this->isExcutable = true;
    if(this->holderButton != NULL && this->holderButton->getState() == DISABLE)
    {
        this->holderButton->changeState(ENABLE);
    }
}

void NormalShootingAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data ==NULL || data->Data == NULL)
    {
        return;
    }
    
    switch (data->Id)
    {
        case PROJECTILE:
            void* pData = data->Data;
            NormalProjectile* projectile = (NormalProjectile *)pData;
            if(projectile != NULL && projectile->getHolder() == this->holder)
            {
                projectile->checkCollisionDataInBeginContact(data, contact, isSideA);
            }
            break;
    }
}

void NormalShootingAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data ==NULL || data->Data == NULL)
    {
        return;
    }
    
    switch (data->Id) {
        case PROJECTILE:
            void* pData = data->Data;
            NormalProjectile* projectile = (NormalProjectile *)pData;
            if(projectile != NULL && projectile->getHolder() == this->holder)
            {
                projectile->checkCollisionDataInEndContact(data, contact, isSideA);
            }
            break;
    }
}