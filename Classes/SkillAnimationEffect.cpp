//
//  SkillAnimationEffect.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 5/21/14.
//
//

#include "SkillAnimationEffect.h"
#include "Util.h"

SkillAnimationEffect::SkillAnimationEffect()
{
    this->minRotateAngle = 0;
    this->maxRotateAngle = 0;
    this->minScale = 1;
    this->maxScale = 1;
    this->repeatTimes = 1;
    
    this->sprite = CCSprite::create();
    this->addChild(sprite);
    this->animationObject = NULL;
    this->isFiniteAction = true;
}

SkillAnimationEffect::~SkillAnimationEffect()
{

}

bool SkillAnimationEffect::init()
{
    return true;
}

void SkillAnimationEffect::update(float dt)
{
    this->sprite->setScale(Util::randomFloatInRange(this->minScale, this->maxScale));
    this->sprite->setRotation(Util::randomFloatInRange(this->minRotateAngle, this->maxRotateAngle));
}

void SkillAnimationEffect::setPosition(CCPoint newPosition)
{
    this->sprite->setPosition(newPosition);
}

void SkillAnimationEffect::run()
{
    CCArray* arrSeq = CCArray::create();
    
    CCCallFunc* stopFunction = CCCallFunc::create(this, callfunc_selector(SkillAnimationEffect::stop));
    CCAnimate* animateAction = CCAnimate::create(this->animationObject->getAnimation());
    if(this->repeatTimes > 0)
    {
        CCRepeat* repeatAction = CCRepeat::create(animateAction, this->repeatTimes);
        arrSeq->addObject(repeatAction);
        arrSeq->addObject(stopFunction);
    }
//    else
//    {
//        arrSeq->addObject(animateAction);
//    }
    action = CCSequence::create(arrSeq);
    action->retain();
    
    this->sprite->runAction(action);
}

void SkillAnimationEffect::stop()
{
    AnimationEffect::stop();
  
    if(this->action != NULL && this->action->isDone() == false)
    {
        this->sprite->stopAction(this->action);
    }
    this->action->release();
    this->action = NULL;
}

//void SkillAnimationEffect::setAnimation(const char* id)
//{
//    AnimationEffect::setAnimation(id);
//}

void SkillAnimationEffect::setAnimation(const char* id, float minRotate, float maxRotate, float minScale, float maxScale, int repeatTimes, CCPoint position)
{
    this->AnimationEffect::setAnimation(id);
    this->minRotateAngle = minRotate;
    this->maxRotateAngle = maxRotate;
    this->minScale = minScale;
    this->maxScale = maxScale;
    this->repeatTimes = repeatTimes;
    setPosition(position);
}

float SkillAnimationEffect::getAnimationDuration()
{
    return this->animationObject->getAnimation()->getDuration();
}
