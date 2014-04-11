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
        
        projectTileList = CCArray::create();
        projectTileList->retain();
    }
}


void NormalShootingAttack::excute()
{
    if(holder != NULL)
    {
        NormalProjectile* proj = new NormalProjectile(this->data, this->holder);
        proj->setGroup(GROUP_SKILL_DEFAULT);
        //
        projectTileList->addObject(proj);
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
    
}

void NormalShootingAttack::stopImmediately()
{
    
}

void NormalShootingAttack::setExcuteAble()
{
    
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
            if(projectile != NULL)
            {
                projectile->BeginContact(contact);
            }
            else
            {
                CCLOG("NULL data");
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
            if(projectile != NULL)
            {
                projectile->EndContact(contact);
            }
            else
            {
                CCLOG("NULL data");
            }
            break;
    }
}