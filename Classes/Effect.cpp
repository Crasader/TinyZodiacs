//
//  Effect.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/18/14.
//
//

#include "Effect.h"
#include "AnimationFactory.h"
#include "PhysicConstants.h"
#include "ScheduleManager.h"
#include "Character.h"

Effect::Effect(EffectData data, GameObject* holder)
{
    this->holder = holder;
    
    this->chance = data.getchance();
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
    
    //    this->sprite = CCSprite::createWithSpriteFrameName("arrow.png");
    if(data.getAnimationId() != "")
    {
        this->sprite = CCSprite::create();
        this->sprite->retain();
        this->animation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(data.getAnimationId().c_str());
        if(this-> animation != NULL && this->animation->getAnimation() != NULL)
        {
            this->animation->getAnimation()->setLoops(INFINITY);
            this->sprite->runAction(CCAnimate::create(this->animation->getAnimation()));
        }
        this->positionOffset = calculatePosition(data.getJointDefA(), data.getJointDefB());
        this->holder->getSprite()->getParent()->addChild(this->sprite,data.getAnimationLayerIndex());
    }
    else
    {
        this->sprite = NULL;
        this->animation = NULL;
    }
    
    //schedule repeat
    CCCallFunc *repeatFuncSelector = CCCallFunc::create(this, callfunc_selector(Effect::onTimeTick));
    this->timeTickRepeatAction = ScheduleManager::getInstance()->scheduleFuctionRepeatly(repeatFuncSelector, this->timeTick, this->lifeTime/this->timeTick);
    
    //schedule life time
    CCCallFunc *callFuncSelector = CCCallFunc::create(this, callfunc_selector(Effect::destroy));
    ScheduleManager::getInstance()->scheduleFuction(callFuncSelector, this->lifeTime);
    //
    this->autorelease();
}

Effect::~Effect()
{
    ScheduleManager::getInstance()->stopScheduledObjectAction(this->timeTickRepeatAction);
    
    if(this->sprite != NULL)
    {
        this->sprite->stopAllActions();
        this->sprite->getParent()->removeChild(this->sprite);
    }
//    this->sprite->release();
//    if(this->animation != NULL)
//    {
//        this->animation->release();
//    }
}

CCPoint Effect::calculatePosition(JointDef jointDefA, JointDef jointDefB)
{
    if(this->holder != NULL && this->animation != NULL)
    {
        CCSize holderSize = CCSize(abs(this->holder->getBodyBoundingBox().lowerBound.x - this->holder->getBodyBoundingBox().upperBound.x)*32,abs(this->holder->getBodyBoundingBox().lowerBound.y - this->holder->getBodyBoundingBox().upperBound.y)*32);
        CCSize thisSize = this->sprite->boundingBox().size;
        
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
    if(this->sprite != NULL)
    {
        this->sprite->setPosition(this->holder->getPositionInPixel()+positionOffset);
    }
}

void Effect::destroy()
{
    this->holder->removeEffect(this);
//    delete this;
}

void Effect::onTimeTick()
{
    CCLOG("tick");
    Character* character = (Character*)this->holder;
//    character->getCharacterData().setHealth(character->getCharacterData().getHealth()-this->health);
    character->notifyByEffect(this);
//    CCLOG("%d - %d",character->getCharacterData().getHealth(),character->getOriginCharacterData().getHealth());
}