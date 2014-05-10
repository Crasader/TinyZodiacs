//
//  Item.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "Item.h"

Item::Item()
{
    this->listAffect = CCArray::create();
    this->listAffect->retain();
    this->lifeTime = 0;
    this->canBePickedUp = false;
}

Item::~Item()
{
    this->listAffect->release();
}

bool Item::init()
{
    if(!GameObject::init())
    {
        return false;
    }
    
    return true;
}

void Item::onCreate()
{
    GameObject::onCreate();
    this->sprite->setScale(0.2f);
    CCScaleTo* scaleTo = CCScaleTo::create(0.2f, 1.0f);
    CCCallFunc* readyToBePickedUp = CCCallFunc::create(this, callfunc_selector(Item::readyToBePickedUp));
    this->sprite->runAction(CCSequence::create(scaleTo,readyToBePickedUp,NULL));
    startSchedule();
    
    PhysicData* physicData = new PhysicData();
    physicData->Id = GAME_ITEM;
    physicData->Data = this;
    body->SetUserData(physicData);
}

void Item::destroy()
{
    this->sprite->stopAllActions();
    if(!this->lifeTimeAction->isDone())
    {
        ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
    }
    this->lifeTimeAction->release();
    
    ItemFactory::getInstance()->destroyItem(this);
}

void Item::prepareToDestroy()
{
    CCFadeIn* fadeIn = CCFadeIn::create(0.2f);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    
    CCRepeat* repeat = CCRepeat::create(CCSequence::create(fadeIn,fadeOut,NULL), 5);
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::destroy));
    CCSequence* seq = CCSequence::create(repeat,destroyFunction,NULL);

    this->sprite->runAction(seq);
}

void Item::readyToBePickedUp()
{
    CCScaleTo* scaleToBig = CCScaleTo::create(0.4f, 1.05f);
    CCScaleTo* scaleToSmall = CCScaleTo::create(0.4f, 1.0f);
    CCRepeatForever* repeateForever = CCRepeatForever::create(CCSequence::create(scaleToBig,scaleToSmall,NULL));
    this->sprite->runAction(repeateForever);
    
    this->canBePickedUp = true;
}

void Item::prepareToPickedUpAndDestroy(CCNode* node)
{
    CCPoint t = node->getPosition() - this->getSprite()->getPosition();
    this->body->SetLinearVelocity(b2Vec2(t.x/PTM_RATIO,t.y/PTM_RATIO));
    this->sprite->setScale(1);
    CCScaleTo* scaleToPickedUp = CCScaleTo::create(0.2f, 0.2);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::destroy));
    this->sprite->runAction(CCSequence::create(CCSpawn::create(scaleToPickedUp,fadeOut,NULL),destroyFunction,NULL));
}

void Item::startSchedule()
{
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::prepareToDestroy));
    this->lifeTimeAction = ScheduleManager::getInstance()->scheduleFunction(destroyFunction, NULL, this->lifeTime, 1);
    this->lifeTimeAction->retain();
}

void Item::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    
}

void Item::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    
}

