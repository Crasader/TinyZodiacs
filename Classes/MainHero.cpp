//
//  MainHero.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/2/14.
//
//

#include "MainHero.h"

MainHero::MainHero()
{
    this->reviveAction = NULL;
    this->goldValue = 0;
}

MainHero::~MainHero()
{
    ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, INVISIBLE_ALL_HERO_CONTROLLER);
}

bool MainHero::init()
{
    if(!Hero::init())
    {
        return false;
    }
    return true;
}


void MainHero::update(float dt)
{
    if(isDead == false)
    {
        Hero::update(dt);
    }
  
}

void MainHero::destroy()
{
    Hero::destroy();
    
    if(this->reviveAction != NULL)
    {
        if(this->reviveAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(this->reviveAction);
        }
        this->reviveAction->release();
        this->reviveAction = NULL;
    }

}

void MainHero::die()
{
    isDead = true;
    ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
    this->sprite->setVisible(false);
    this->body->SetActive(false);
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->setVisible(false);
    }
    this->reviveAction = ScheduleManager::getInstance()->scheduleFunction(CCCallFunc::create(this, callfunc_selector(MainHero::revive)), NULL, 5, 1);
    this->reviveAction->retain();
    
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    EffectManager::getInstance()->runEffect(effect, getPositionInPixel(),ABOVE_CHARACTER_LAYER);
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, INVISIBLE_ALL_HERO_CONTROLLER);
    this->body->SetLinearVelocity(b2Vec2(0,0));
    
    cleanAllAffect();

}

void MainHero::revive()
{
    this->isDead = false;
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    this->sprite->setVisible(true);
    this->body->SetActive(true);
    
    setcharacterData(this->originCharacterData);
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->setVisible(true);
        this->gameObjectView->notifyChange();
    }
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, VISIBLE_ALL_HERO_CONTROLLER);
    setPositionInPixel(this->revivePosition);
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    EffectManager::getInstance()->runEffect(effect, getPositionInPixel());
    this->body->SetLinearVelocity(b2Vec2(0,0));
//    this->release();
////    destroy();
//      ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
//       ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, INVISIBLE_ALL_HERO_CONTROLLER);
    
    this->reviveAction->release();
    this->reviveAction = NULL;

}

void MainHero::pickUp(Item* item)
{
    Hero::pickUp(item);
    if(item->getGameObjectID() == GOLD_ITEM)
    {
        GoldItem* goldItem = static_cast<GoldItem*>(item);
        this->goldValue += goldItem->getGoldValue();
        
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_GOLD_VALUE,new int(this->goldValue));
    }
}

