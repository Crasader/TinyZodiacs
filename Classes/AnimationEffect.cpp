//
//  AnimationEffect.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "AnimationEffect.h"
#include "DataCollector.h"
#include "ScheduleManager.h"


AnimationEffect::AnimationEffect()
{
    this->sprite = CCSprite::create();
    this->addChild(sprite);
    this->animationObject = NULL;
    this->stopAction = NULL;
}

AnimationEffect::~AnimationEffect()
{
}

bool AnimationEffect::init()
{
    return true;
}

void AnimationEffect::run()
{
    CCCallFunc* stopFunction = CCCallFunc::create(this, callfunc_selector(AnimationEffect::stop));
    CCAnimate* animateAction = CCAnimate::create(this->animationObject->getAnimation());
    
    CCArray* arrSeq = CCArray::create();
    arrSeq->addObject(animateAction);
    arrSeq->addObject(stopFunction);
    
    this->sprite->runAction(CCSequence::create(arrSeq));
}

void AnimationEffect::stop()
{
    if(stopAction != NULL)
    {
        ScheduleManager::getInstance()->scheduleFuction(stopAction, 0);
        this->stopAction->release();
    }
    
    this->sprite->stopAllActions();
    this->removeFromParent();
}

void AnimationEffect::update(float dt)
{
    
}

void AnimationEffect::setAnimation(const char *id)
{
    this->animationObject = DataCollector::getInstance()->getAnimationObjectByKey(id);
}

void AnimationEffect::setAnimation(const char* id, bool flipX)
{
    this->animationObject = DataCollector::getInstance()->getAnimationObjectByKey(id);
    this->sprite->setFlipX(flipX);
}

void AnimationEffect::setOpacity(GLubyte opacity)
{
    if(this->sprite != NULL)
    {
        this->sprite->setOpacity(opacity);
    }
}

void AnimationEffect::setStopAction(CCCallFunc* action)
{
    this->stopAction = action;
    this->stopAction->retain();
}