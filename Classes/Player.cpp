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


}

bool Player::init()
{
    this->scheduleUpdate();
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