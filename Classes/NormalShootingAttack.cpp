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
#include "GameObjectManager.h"


NormalShootingAttack::NormalShootingAttack(GameObject* holder, NormalShootingSkillData data): AbstractSkill(holder,data)
{
    if(holder != NULL)
    {
        this->data = data;
        this->isExcutable = true;
        this->autoShootAction = NULL;
        shootedTime =1;
    }
}

NormalShootingAttack::~NormalShootingAttack()
{
    this->data.releaseEffectLists();
    //    CCObject* obj;
    //    CCARRAY_FOREACH(projectTileList, obj)
    //    {
    //        ((NormalProjectile*)obj)->remove();
    //    }
    //    projectTileList->release();
}

void NormalShootingAttack::excute()
{
    if(this->isDisable == false && this->getIsExcutable())
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
            
            if(this-> skillButtonID != UNKNOWN)
            {
                //                this->holderButton->changeState(DISABLE);
                StateCommandData *data = new StateCommandData();
                data->controllerId = this->skillButtonID;
                data->isActive = false;
                this->holder->notifyUIChange(data);
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
    //    for(unsigned int i=0; i< projectTileList->count() ; i++)
    //    {
    //        if(((NormalProjectile*)projectTileList->objectAtIndex(i)) != NULL)
    //        {
    //            ((NormalProjectile*)projectTileList->objectAtIndex(i))->update(dt);
    //        }
    //    }
    
    if(this->skillButtonID != UNKNOWN)
    {
        if(this->isExcutable)
        {
        }
        else
        {
            StateCommandData *data = new StateCommandData();
            data->controllerId = this->skillButtonID;
            data->isActive = false;
            this->holder->notifyUIChange(data);
        }
    }
}

void NormalShootingAttack::onCreate()
{
    
}

void NormalShootingAttack::destroy()
{
    AbstractSkill::destroy();
}

void NormalShootingAttack::setPhysicGroup(uint16 group)
{
    
}

void NormalShootingAttack::excuteImmediately()
{
    if(this->isDisable == false && holder != NULL)
    {
        //
        Util::applyEffectFromList(data.getlistSelfEffect(), this->holder);
        //shoot first projectile
        NormalShootingSkillData calculatedSkillData = this->data;
        calculateSkillData(&calculatedSkillData, ((Character*)this->holder)->getcharacterData());

        this->calculatedGameObjectData = this->holder->getCalculatedData();
        calculatedSkillData.setPositionPlusPerUnit(ccp((this->shootedTime-1)*calculatedSkillData.getPositionPlusPerUnit().x,(this->shootedTime-1)*calculatedSkillData.getPositionPlusPerUnit().y));
        
        NormalProjectile* proj = NormalProjectile::create();
        proj->initDataAndShoot(calculatedSkillData, this->calculatedGameObjectData, GROUP_SKILL_DEFAULT);
        //
        if(this->autoShootAction != NULL)
        {
            if(this->autoShootAction->isDone()==false)
            {
                ScheduleManager::getInstance()->stopAction(this->autoShootAction);
                this->autoShootAction->release();
            }
        }
        this->autoShootAction = CCCallFunc::create(this, callfunc_selector(NormalShootingAttack::autoShoot));
        this->autoShootAction->retain();
        ScheduleManager::getInstance()->scheduleFuctionRepeatly(this->autoShootAction, this->data.getDelayPerShoot(), this->data.getQuantity()-1);
        //add projectile to manager
        
    }
}

void NormalShootingAttack::stopImmediately()
{
    
}

void NormalShootingAttack::setExcuteAble()
{
    this->isExcutable = true;
    //    if(this->holderButton != NULL && this->holderButton->getState() == DISABLE)
    //    {
    //        this->holderButton->changeState(ENABLE);
    //    }
    if(this->skillButtonID != UNKNOWN)
    {
        StateCommandData *data = new StateCommandData();
        data->controllerId = this->skillButtonID;
        data->isActive = true;
        this->holder->notifyUIChange(data);
    }
}

void NormalShootingAttack::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(this->isDisable)
    {
        return;
    }
    //    if(data ==NULL || data->Data == NULL)
    //    {
    //        return;
    //    }
    
}

void NormalShootingAttack::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(this->isDisable)
    {
        return;
    }
    //    if(data == NULL || data->Data == NULL)
    //    {
    //        return;
    //    }
}

void NormalShootingAttack::autoShoot()
{
    if(this->isDisable)
    {
        return;
    }
    
    
    NormalShootingSkillData calculatedSkillData = this->data;
    calculateSkillData(&calculatedSkillData, ((Character*)this->holder)->getcharacterData());
    
    this->shootedTime++;
    calculatedSkillData.setPositionPlusPerUnit(ccp((this->shootedTime-1)*calculatedSkillData.getPositionPlusPerUnit().x,(this->shootedTime-1)*calculatedSkillData.getPositionPlusPerUnit().y));
    //
    calculatedSkillData.setAngle(CC_DEGREES_TO_RADIANS(this->data.getAngle()+Util::randomFloatInRange(- calculatedSkillData.getAngleVariability(), calculatedSkillData.getAngleVariability())));
    //
    NormalProjectile* proj = NormalProjectile::create();
    proj->initDataAndShoot(calculatedSkillData, this->calculatedGameObjectData, GROUP_SKILL_DEFAULT);
    //
    if(this->shootedTime == this->data.getQuantity())
    {
        this->shootedTime =1;
    }
}

void NormalShootingAttack::stopAllAction()
{
    AbstractSkill::stopAllAction();
    if(this->autoShootAction != NULL)
    {
        if(this->autoShootAction->isDone()==false)
        {
            ScheduleManager::getInstance()->stopAction(this->autoShootAction);
            this->autoShootAction->release();
        }
        this->autoShootAction=NULL;
    }
}