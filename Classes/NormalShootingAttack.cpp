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
        
        this->autorelease();
        
        this->excuteAction = this->stopAction = this->coolDownAction = NULL;

    }
}


void NormalShootingAttack::excute()
{
    if(this->getIsExcutable())
    {
        if(this->excuteAction != NULL)
        {
            this->excuteAction->stop();
            this->excuteAction->release();
        }
        CCCallFunc* excuteFunc = CCCallFunc::create(this, callfunc_selector(AbstractSkill::excuteImmediately));
        this->excuteAction =  ScheduleManager::getInstance()->scheduleFuction(excuteFunc, this->data.getDelay());
        this->excuteAction->retain();
        
        if(this->data.getCoolDown() > 0)
        {
            if(this->coolDownAction != NULL)
            {
                this->coolDownAction->stop();
                this->coolDownAction->release();
            }
            CCCallFunc* coolDownFunc = CCCallFunc::create(this, callfunc_selector(AbstractSkill::setExcuteAble));
            this->coolDownAction = ScheduleManager::getInstance()->scheduleFuction(coolDownFunc, this->data.getCoolDown());
            this->coolDownAction->retain();
            
            this->isExcutable = false;
            if(this-> holderButton != NULL)
            {
                this->holderButton->changeState(DISABLE);
            }
        }
//        else
//        {
//            this->AbstractSkill::excuteImmediately();
//        }
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

void NormalShootingAttack::setPhysicGroup(uint16 group)
{
    this->group = group;
}

void NormalShootingAttack::excuteImmediately()
{
    if(holder != NULL)
    {
//        NormalProjectile* proj = new NormalProjectile(this->data, this->holder, this->projectTileList);
        NormalProjectile* proj = NormalProjectile::create();
        proj->setData(this->data, this->holder, this->projectTileList);
        proj->setGroup(GROUP_SKILL_DEFAULT);
//        proj->retain();
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
        {
            void* pData = data->Data;
            NormalProjectile* projectile = static_cast<NormalProjectile*>(pData);
            if(projectile != NULL && projectile->getHolder() == this->holder)
            {
                projectile->checkCollisionDataInBeginContact(data, contact, isSideA);
            }
            break;
        }
        default:
            break;
    }
}

void NormalShootingAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data == NULL || data->Data == NULL)
    {
        return;
    }
    
    switch (data->Id) {
        case PROJECTILE:
        {
            void* pData = data->Data;
            NormalProjectile* projectile = (NormalProjectile *)pData;
            if(projectile != NULL && projectile->getHolder() == this->holder)
            {
                projectile->checkCollisionDataInEndContact(data, contact, isSideA);
            }
            break;
        }
        default:
            break;
    }
}