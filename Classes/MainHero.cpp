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

    effect->setAnimation("effect-explosion3");

    EffectManager::getInstance()->runEffect(effect, getPositionInPixel(),ABOVE_CHARACTER_LAYER);
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, INVISIBLE_ALL_HERO_CONTROLLER);
    this->body->SetLinearVelocity(b2Vec2(0,0));
    
    CCObject* skill;
    CCARRAY_FOREACH(this->listSkill, skill)
    {
        ((AbstractSkill*)skill)->stopImmediately();
    }
    
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
    effect->setAnimation("effect-explosion");
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

bool MainHero::receiveCommand(CommandID commandID, void* data)
{
    Hero::receiveCommand(commandID, data);
    
    switch (commandID)
    {
        case HERO_CREATE_DEFENSE:
        {
            DefenseDTO* defenseDTO = static_cast<DefenseDTO*>(data);
            
            TowerStructDTO* towerStructDTO = new TowerStructDTO();
            towerStructDTO->group = this->group;
            towerStructDTO->id = defenseDTO->id;
            towerStructDTO->positionX = this->getPositionInPixel().x;
            towerStructDTO->positionY = this->getPositionInPixel().y;
            
            
            
            Tower* tower = ObjectFactory::createTower(towerStructDTO, GameManager::getInstance()->getGameplayHolder().worldHolder);
            tower->setGameObjectView(InfoViewCreator::createTowerView(tower, NULL));
            
            tower->attachSpriteTo(GameManager::getInstance()->getGameplayHolder().nodeHolder);
            GameObjectManager::getInstance()->addGameObject(tower);
            
            this->goldValue -= defenseDTO->cost;
            if(this->goldValue <= 0)
            {
                this->goldValue = 0;
            }
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_GOLD_VALUE,new int(this->goldValue));
        }
            break;
            
        default:
            break;
    }
    
    return true;
}
