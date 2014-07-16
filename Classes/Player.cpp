//
//  Player.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "Player.h"
#include "ControllerManager.h"

Player::Player()
{
    this->hero = NULL;
    this->achievement = new Achievement();
}

Player::~Player()
{
    delete this->achievement;
}

bool Player::init()
{
    this->scheduleUpdate();
    
    ControllerManager::getInstance()->registerController(PLAYER_CONTROLLER, this);
    
    return true;
}

void Player::update(float dt)
{
    
}

void Player::attachWithHero(Hero* hero)
{
    if(hero != NULL)
    {
        //    this->hero = hero;
    }
}

void Player::attachWithHero(const char* heroID)
{
    this->hero = ObjectFactory::createMainHero(heroID);
    this->hero->setPositionInPixel(ccp(3000,1076));
    this->hero->setGroup(A);
    this->hero->setGameObjectView(InfoViewCreator::createHeroView(this->hero, NULL));
    GameObjectManager::getInstance()->addGameObject(this->hero);
}

void Player::reviveHero()
{
    // this->hero->revive();
}

bool Player::receiveCommand(CommandID commandID, void* data)
{
    switch (commandID) {
        case RECIEVE_GOLD:
        {
            int* goldValue = static_cast<int*>(data);
            this->achievement->addGold(*goldValue);
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_GOLD_VALUE,new int(this->achievement->getGold()));
            delete goldValue;
            break;
        }
            
        case RECIEVE_SCORE:
        {
            int* score = static_cast<int*>(data);
            this->achievement->addScore(*score);
            delete score;
            
            break;
        }
        case RECIEVE_TIME:
        {
            int* time = static_cast<int*>(data);
            this->achievement->setTime(*time);
            delete time;
            
            break;
        }
        case PLAYER_CREATE_DEFENSE:
        {
            DefenseDTO* defenseDTO = static_cast<DefenseDTO*>(data);
            
            TowerStructDTO* towerStructDTO = new TowerStructDTO();
            towerStructDTO->group = this->getHero()->getGroup();
            towerStructDTO->id = defenseDTO->id;
            towerStructDTO->positionX = this->getHero()->getPositionInPixel().x;
            towerStructDTO->positionY = this->getHero()->getPositionInPixel().y;
            
            Tower* tower = ObjectFactory::createTower(towerStructDTO, GameManager::getInstance()->getGameplayHolder().worldHolder);
            tower->setGameObjectView(InfoViewCreator::createTowerView(tower, NULL));
            
            tower->attachSpriteTo(GameManager::getInstance()->getGameplayHolder().nodeHolder);
            GameObjectManager::getInstance()->addGameObject(tower);
            
            this->getAchievement()->addGold(-defenseDTO->cost);
            if(this->getAchievement()->getGold() <= 0)
            {
                this->getAchievement()->setGold(0);
            }
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_GOLD_VALUE,new int(this->getAchievement()->getGold()));
            
            break;
        }
            
        default:
            break;
    }
    return true;
}