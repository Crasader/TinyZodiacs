//
//  HealthPointEffect.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#include "HealthPointEffect.h"
#include "AnimationLoader.h"

HealthPointEffect::HealthPointEffect()
{
    healthPoint = 0;
    label = CCLabelTTF::create("", "Marker Felt",70);
    label->setColor(ccc3(255,0,0));
    label->setOpacity(200);
    this->addChild(label);
}

HealthPointEffect::~HealthPointEffect()
{
    //this->sprite->removeFromParent();
}

bool HealthPointEffect::init()
{
    return true;
}

void HealthPointEffect::run()
{
    CCMoveBy* moveBy  =  CCMoveBy::create(0.5f, ccp(0,200));
    CCJumpBy* jumpBy = CCJumpBy::create(0.5f, ccp(CCRANDOM_MINUS1_1()*30,10), 100, 1);

    CCFadeOut* fadeOut = CCFadeOut::create(0.6f);
    CCScaleBy* scaleBy = CCScaleBy::create(0.5f, 0.75f);
    CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(HealthPointEffect::stop));
    
    
    
    CCArray* arr = CCArray::create();
    arr->addObject(jumpBy);
    arr->addObject(fadeOut);
    arr->addObject(scaleBy);
    
    CCArray* seq = CCArray::create();
    seq->addObject(CCSpawn::create(arr));
    seq->addObject(func);
    //
    //    this->sprite->runAction(animate);
    this->label->runAction(CCSequence::create(seq));
    
    
}

void HealthPointEffect::stop()
{
    this->label->stopAllActions();
    this->removeFromParent();
}

void HealthPointEffect::setHealthPoint(float hp)
{
    this->healthPoint = hp;
    this->label->setString(CCString::createWithFormat("%0.0f", this->healthPoint)->getCString());
}

void HealthPointEffect::update(float dt)
{
   }