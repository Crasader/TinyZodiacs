//
//  Item.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "Item.h"
#include "ItemFactory.h"

Item::Item()
{
    id = 0;
    this->gameObjectID = ITEM;
    this->lifeTime = 0;
    this->isActive = false;
    this->lifeTimeAction = NULL;
    
    this->prepareToAppearAnimation = NULL;
    this->prepareToDisappearAnimation = NULL;
    this->appearAnimation = NULL;
}

Item::~Item()
{
    this->sprite->stopAllActions();
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

    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        PhysicData* physicData = new PhysicData();
        physicData->BodyId = GAME_ITEM;
        physicData->GameObjectID = this->gameObjectID;
        physicData->Data = this;
        
        f->SetUserData(physicData);
    }
    
    prepareToAppear();
}

void Item::destroy()
{
    
    if(!this->isDestroyed)
    {
        this->sprite->stopAllActions();
        if(this->lifeTimeAction != NULL)
        {
            if(!this->lifeTimeAction->isDone())
            {
                ScheduleManager::getInstance()->stopAction(this->lifeTimeAction);
            }
            this->lifeTimeAction->release();
        }
    }
    GameObject::destroy();
}

void Item::startSchedule()
{
    CCCallFunc* disappearFunction = CCCallFunc::create(this, callfunc_selector(Item::prepareToDisappearInTimeOut));
    this->lifeTimeAction = ScheduleManager::getInstance()->scheduleFunction(disappearFunction, NULL, this->lifeTime, 1);
    this->lifeTimeAction->retain();
}

void Item::prepareToAppear()
{
    this->sprite->setScale(0);
    CCScaleTo* scaleTo = CCScaleTo::create(0.2f, 1.0f);
    CCCallFunc* appearFunction = CCCallFunc::create(this, callfunc_selector(Item::appear));
    this->sprite->runAction(CCSequence::create(scaleTo,appearFunction,NULL));
}

void Item::appear()
{
    if(this->appearAnimation != NULL)
    {
        CCAnimate* animate = CCAnimate::create(this->appearAnimation->getAnimation());
        this->sprite->runAction(animate);
    }
    
    CCScaleTo* scaleToBig = CCScaleTo::create(0.4f, 1.05f);
    CCScaleTo* scaleToSmall = CCScaleTo::create(0.4f, 1.0f);
    CCRepeatForever* repeateForever = CCRepeatForever::create(CCSequence::create(scaleToBig,scaleToSmall,NULL));
    this->sprite->runAction(repeateForever);
    
    startSchedule();
    
    this->isActive = true;
}

void Item::prepareToDisappearInTimeOut()
{
    CCFadeIn* fadeIn = CCFadeIn::create(0.2f);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    
    CCRepeat* repeat = CCRepeat::create(CCSequence::create(fadeIn,fadeOut,NULL), 5);
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::disappear));
    
    this->sprite->runAction(CCSequence::create(repeat,destroyFunction,NULL));
}

void Item::prepareToDisappearInContact(GameObject* contactGameObject)
{
    if(contactGameObject != NULL)
    {
        CCPoint t = contactGameObject->getPositionInPixel() - this->getSprite()->getPosition();
        this->body->SetLinearVelocity(b2Vec2(t.x/PTM_RATIO,t.y/PTM_RATIO));
    }
    
    
    this->sprite->setScale(1);
    CCScaleTo* scaleToPickedUp = CCScaleTo::create(0.2f, 0.2);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    CCCallFunc* destroyFunction = CCCallFunc::create(this, callfunc_selector(Item::disappear));
    
    this->sprite->runAction(CCSequence::create(CCSpawn::create(scaleToPickedUp,fadeOut,NULL),destroyFunction,NULL));
}

void Item::prepareToDisappearInOpen()
{
    CCArray* arrSeq = CCArray::create();
    if(this->prepareToDisappearAnimation != NULL)
    {
        CCAnimate* animate = CCAnimate::create(this->prepareToDisappearAnimation->getAnimation());
        arrSeq->addObject(animate);
    }
    CCCallFunc* disappearFunction = CCCallFunc::create(this, callfunc_selector(Item::disappear));
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    arrSeq->addObject(fadeOut);
    arrSeq->addObject(disappearFunction);
    this->sprite->runAction(CCSequence::create(arrSeq));
}

void Item::disappear()
{
    destroy();
}

void Item::contact(GameObject* contactGameObject)
{
    if(!this->isDestroyed)
    {
        prepareToDisappearInContact(contactGameObject);
    }
}

void Item::open(GameObject* openGameObject)
{
    
}

void Item::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
 
    if(!this->isActive)
    {
        return;
    }
    if(holderData->Data == this)
    {
        if(collisionData != NULL)
        {
            switch (collisionData->GameObjectID) {
                case SKILL_OBJECT:
                {
                    AbstractSkill* skill = static_cast<AbstractSkill*>(collisionData->Data);
                    if(!skill->getIsDisable())
                    {
                        open(skill->getHolder());
                    }
                }
                    break;
                    
                    
                default:
                    break;
            }
        }
    }
    
}

void Item::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
}

void Item::attachSpriteTo(CCNode* node)
{
    node->addChild(this->getSprite(),ABOVE_CHARACTER_LAYER);
}

void Item::attach(Observer* observer)
{
    GameObject::attach(observer);
}

void Item::detach(Observer* observer)
{
    GameObject::detach(observer);
}

void Item::notifyToDestroy()
{
    GameObject::notifyToDestroy();
}


