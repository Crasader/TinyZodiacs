//
//  Player.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "Player.h"

Player::Player()
{
    this->hero = NULL;
}

Player::~Player()
{
    this->hero->release();
}

bool Player::init()
{
    this->scheduleUpdate();
    return true;
}

void Player::update(float dt)
{
    this->hero->update(dt);
}

void Player::attachWithHero(Hero* hero)
{
    if(hero != NULL)
    {
        this->hero = hero;
    }
}

void Player::attachWithHero(const char* heroID)
{
    this->hero = ObjectFactory::createHero(DataCollector::getInstance()->getHeroDTOByKey(heroID), GameManager::getInstance()->getGameplayHolder().worldHolder, false);
    this->hero->setPositionInPixel(ccp(2500,500));
    this->hero->setGroup(A);
    

    
    this->hero->setGameObjectView(InfoViewCreator::createHeroView(this->hero, NULL));
    this->hero->retain();
}

void Player::reviveHero()
{
    this->hero->revive();
}