//
//  Effect.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/18/14.
//
//

#include "Effect.h"
#include "PhysicConstants.h"
#include "ScheduleManager.h"
#include "Character.h"
#include "DataCollector.h"
#include "SkillAnimationEffect.h"
#include "EffectManager.h"

Effect::Effect(EffectData data, GameObject* holder)
{
    this->holder = holder;
    
    this->chance = data.getChance();
    this->critChance = data.getCritChance();
    this->critRatio = data.getCritRatio();
    this->health = data.getHealth();
    this->attack = data.getAttack();
    this->attackSpeed = data.getAttack();
    this->speed = data.getSpeed();
    this->defense = data.getDefense();
    this->maxJump = data.getMaxJump();
    this->jumpHeight = data.getJumpHeight();
    
    this->lifeTime = data.getLifeTime();
    this->timeTick = data.gettimeTick();
    
    if(data.getAnimationId() != "")
    {
//        this->sprite = CCSprite::create();
//        this->sprite->retain();
//        this->animation = DataCollector::getInstance()->getAnimationObjectByKey(data.getAnimationId().c_str());
//        if(this->animation != NULL)
//        {
//            if(this->animation->getAnimation() != NULL)
//            {
//                this->animation->getAnimation()->setLoops(INFINITY);
//                this->sprite->runAction(CCAnimate::create(this->animation->getAnimation()));
//            }
//        }
//        this->positionOffset = calculatePosition(data.getJointDefA(), data.getJointDefB());
//        this->holder->getSprite()->getParent()->addChild(this->sprite,data.getAnimationLayerIndex());
        
        this->animation = SkillAnimationEffect::create();
        this->animation->retain();
        ((SkillAnimationEffect*)this->animation)->setAnimation(data.getAnimationId().c_str(), data.getMinRotateAngle(), data.getMaxRotateAngle(), data.getMinScale(), data.getMaxScale(), data.getRepeatTimes(), CCPoint(0, 0));
        
        if(data.getRepeatTimes() <=0)
        {
            int repeatTime = data.getRepeatTimes();
            repeatTime = data.getLifeTime() / ((SkillAnimationEffect*)this->animation)->getAnimationDuration();
            ((SkillAnimationEffect*)this->animation)->setRepeatTimes(repeatTime);
            ((SkillAnimationEffect*)this->animation)->setIsFiniteAction(false);
        }
        
        EffectManager::getInstance()->runEffect((SkillAnimationEffect*)this->animation, CCPoint(0, 0), data.getAnimationLayerIndex());
    }
    else
    {
//        this->sprite = NULL;
        this->animation = NULL;
    }
    
    //schedule repeat
    CCCallFunc *timeTickFunction = CCCallFunc::create(this, callfunc_selector(Effect::onTimeTick));
    CCCallFunc *destroyFunction = CCCallFunc::create(this, callfunc_selector(Effect::destroy));
    
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
    
    this->autorelease();
    //Calculate
    calculateActualInformation(holder);
}

void Effect::calculateActualInformation(GameObject* holder)
{
    //this->health+= ((Character*)holder)->getcharacterData().getAttack();
}

Effect::~Effect()
{
//    if(this->sprite != NULL)
//    {
//        this->sprite->stopAllActions();
//        this->sprite->removeFromParent();
//    }

}

CCPoint Effect::calculatePosition(JointDef jointDefA, JointDef jointDefB)
{
    if(this->holder != NULL && this->animation != NULL)
    {
        CCSize holderSize = CCSize(abs(this->holder->getBodyBoundingBox().lowerBound.x - this->holder->getBodyBoundingBox().upperBound.x)*32,abs(this->holder->getBodyBoundingBox().lowerBound.y - this->holder->getBodyBoundingBox().upperBound.y)*32);
        CCSize thisSize = ((SkillAnimationEffect*)this->animation)->sprite->boundingBox().size;
        
        CCPoint p1 = calculate(holderSize, jointDefA.x, jointDefA.y, jointDefA.offsetX, jointDefA.offsetY);
        CCPoint p2 = calculate(thisSize, jointDefB.x, jointDefB.y, jointDefB.offsetX, jointDefB.offsetY);
        
        CCPoint offset = p1+p2;
        return offset;
    }
    return ccp(0,0);
}

CCPoint Effect::calculate(CCSize boundingBox, int typeX, int typeY, float offsetX, float offsetY)
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

void Effect::update(float dt)
{
    if(this->animation != NULL)
    {
        ((SkillAnimationEffect*)this->animation)->setPosition(this->holder->getPositionInPixel()+positionOffset);
    }
}

void Effect::stopAllSchedule()
{
    if(!this->timeTickRepeatAction->isDone())
    {
        ScheduleManager::getInstance()->stopAction(this->timeTickRepeatAction);
    }
    if(!this->lifeTimeAction->isDone())
    {
        ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
    }
    
    this->timeTickRepeatAction->release();
    this->lifeTimeAction->release();
}

void Effect::destroy()
{
//    if(!this->timeTickRepeatAction->isDone())
//    {
//        ScheduleManager::getInstance()->stopAction(this->timeTickRepeatAction);
//    }
//    if(!this->lifeTimeAction->isDone())
//    {
//    ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
//    }
//    
//    this->timeTickRepeatAction->release();
//    this->lifeTimeAction->release();
    this->stopAllSchedule();
    
    if(((SkillAnimationEffect*)this->animation)->getIsFiniteAction() == false)
    {
        EffectManager::getInstance()->stopEffect(this->animation);
    }
    this->animation->release();
    
    this->holder->removeEffect(this);
    
}

void Effect::onTimeTick()
{
    Character* character = (Character*)this->holder;

    character->notifyByEffect(this);
    
    setDataAfterFirstTick();
}

void Effect::setDataAfterFirstTick()
{
    this->attack = 0;
    this->attackSpeed = 0;
    this->speed = 0;
    this->defense = 0;
    this->maxJump = 0;
    this->jumpHeight = 0;
}