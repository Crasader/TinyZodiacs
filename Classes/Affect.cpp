//
//  Affect.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/18/14.
//
//

#include "Affect.h"
#include "PhysicConstants.h"
#include "ScheduleManager.h"
#include "Character.h"
#include "DataCollector.h"
#include "EffectManager.h"

Affect::Affect()
{
    this->animation = NULL;
    this->isDestroyed = false;
    this->timeTickRepeatAction = NULL;
    this->lifeTimeAction = NULL;
}

Affect::~Affect()
{
    this->holder = NULL;
}

CCPoint Affect::calculatePosition(JointDef jointDefA, JointDef jointDefB)
{
    if(this->holder != NULL && this->animation != NULL)
    {
        CCSize holderSize = CCSize(abs(this->holder->getBodyBoundingBox().lowerBound.x - this->holder->getBodyBoundingBox().upperBound.x)*32,abs(this->holder->getBodyBoundingBox().lowerBound.y - this->holder->getBodyBoundingBox().upperBound.y)*32);
        CCSize thisSize = this->animation->sprite->boundingBox().size;
        
        CCPoint p1 = calculate(holderSize, jointDefA.x, jointDefA.y, jointDefA.offsetX, jointDefA.offsetY);
        CCPoint p2 = calculate(thisSize, jointDefB.x, jointDefB.y, jointDefB.offsetX, jointDefB.offsetY);
        
        CCPoint offset = p1+p2;
        return offset;
    }
    return ccp(0,0);
}

CCPoint Affect::calculate(CCSize boundingBox, int typeX, int typeY, float offsetX, float offsetY)
{
    CCPoint point = CCPoint(0, 0);
    float widthHalf = boundingBox.width/2;
    float heightHalf= boundingBox.height/2;
    
    if(typeX == JOINT_REAR)
    {
        if(holder->getDirection() == LEFT)
        {
            typeX = JOINT_BOTTOM_OR_LEFT;
        }
        else if(holder->getDirection() == RIGHT)
        {
            typeX = JOINT_TOP_OR_RIGHT;
        }
    }
    
    if(typeY == JOINT_REAR)
    {
        if(holder->getDirection() == LEFT)
        {
            typeY = JOINT_BOTTOM_OR_LEFT;
        }
        else if(holder->getDirection() == RIGHT)
        {
            typeY = JOINT_TOP_OR_RIGHT;
        }
    }
    
    //
    point.x = typeX*(widthHalf+offsetX);
    point.y = typeY*(heightHalf+offsetY);
    
    return point;
}

void Affect::update(float dt)
{
    if(this->isDestroyed == false)
    {
        if(this->animation != NULL)
        {
            this->animation->update(dt);
            this->animation->setPosition(this->holder->getPositionInPixel()+positionOffset);
        }
    }
}

void Affect::stopAllSchedule()
{
    if(this->timeTickRepeatAction != NULL)
    {
        if(!this->timeTickRepeatAction->isDone())
        {
            ScheduleManager::getInstance()->stopAction(this->timeTickRepeatAction);
        }
        this->timeTickRepeatAction->release();
        this->timeTickRepeatAction = NULL;
    }
    if(this->lifeTimeAction != NULL)
    {
        if(!this->lifeTimeAction->isDone())
        {
            ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
        }
        this->lifeTimeAction->release();
        this->lifeTimeAction = NULL;
    }
}


void Affect::destroy()
{
    if(this->isDestroyed == false)
    {
        this->isDestroyed = true;
        stopAllSchedule();
        
        if(this->animation->getIsFiniteAction() == false)
        {
            EffectManager::getInstance()->stopEffect(this->animation);
        }
        this->animation->release();
        this->animation = NULL;
        
        this->holder = NULL;
    }
}

void Affect::destroyOnTimeOut()
{
    if(this->isDestroyed == false)
    {
        this->isDestroyed = true;
        stopAllSchedule();
        
        if(this->animation->getIsFiniteAction() == false)
        {
            EffectManager::getInstance()->stopEffect(this->animation);
        }
        this->animation->release();
        this->animation = NULL;
        
        this->holder->removeAffect(this);
    }
}

void Affect::onTimeTick()
{
    if(this->holder != NULL)
    {
        if(this->isDestroyed == false)
        {
            Character* character =static_cast<Character*>(this->holder) ;
            
            if(character!=NULL)
                character->notifyByAffect(this);
            
            setDataAfterFirstTick();
        }
    }
}

void Affect::setDataAfterFirstTick()
{
    this->attack = 0;
    this->attackSpeed = 0;
    this->speed = 0;
    this->defense = 0;
    this->maxJump = 0;
    this->jumpHeight = 0;
}

void Affect::start()
{
    //schedule repeat
    CCCallFunc *timeTickFunction = CCCallFunc::create(this, callfunc_selector(Affect::onTimeTick));
    CCCallFunc *destroyFunction = CCCallFunc::create(this, callfunc_selector(Affect::destroyOnTimeOut));
    
    if(this->timeTick == 0)
    {
        this->timeTickRepeatAction = ScheduleManager::getInstance()->scheduleFunction(timeTickFunction, NULL, 0, 1);
    }
    else
    {
        this->timeTickRepeatAction = ScheduleManager::getInstance()->scheduleFunctionForever(timeTickFunction, NULL, this->timeTick);
    }
    this->timeTickRepeatAction->retain();
    
    this->lifeTimeAction = ScheduleManager::getInstance()->scheduleFunction(destroyFunction, NULL,this->lifeTime, 1);
    this->lifeTimeAction->retain();
    
    EffectManager::getInstance()->runEffect(this->animation, CCPoint(0, 0), animationLayerIndex);
}

bool Affect::init()
{
    return true;
}

void Affect::setData(EffectData effectData)
{
    this->chance = effectData.getChance();
    this->critChance = effectData.getCritChance();
    this->critRatio = effectData.getCritRatio();
    this->health = effectData.getHealth();
    this->attack = effectData.getAttack();
    this->attackSpeed = effectData.getAttack();
    this->speed = effectData.getSpeed();
    this->defense = effectData.getDefense();
    this->maxJump = effectData.getMaxJump();
    this->jumpHeight = effectData.getJumpHeight();
    
    this->lifeTime = effectData.getLifeTime();
    this->timeTick = effectData.gettimeTick();
    this->animationLayerIndex = effectData.getAnimationLayerIndex();
    
    if(effectData.getAnimationId() != "")
    {
        this->animation = SkillAnimationEffect::create();
        this->animation->retain();
        this->animation->setAnimation(effectData.getAnimationId().c_str(), effectData.getMinRotateAngle(), effectData.getMaxRotateAngle(), effectData.getMinScale(), effectData.getMaxScale(), effectData.getRepeatTimes(), CCPoint(0, 0));
        
        if(effectData.getRepeatTimes() <= 0)
        {
            int repeatTime = effectData.getRepeatTimes();
            repeatTime = effectData.getLifeTime() / ((SkillAnimationEffect*)this->animation)->getAnimationDuration();
            this->animation->setRepeatTimes(repeatTime);
            this->animation->setIsFiniteAction(false);
        }

    }
}

void Affect::setHolder(GameObject* holder)
{
    this->holder = holder;
}
