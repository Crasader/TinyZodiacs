//
//  GameMatch.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/22/14.
//
//

#include "GameMatch.h"
#include "MapCreator.h"

GameMatch::GameMatch()
{
    this->gameWorld = NULL;
}

GameMatch::~GameMatch()
{
    
}

bool GameMatch::init()
{
    this->gameWorld = GameWorld::create();
    this->addChild(this->gameWorld);
    
    return true;
}

void GameMatch::update(float dt)
{
    
}

void GameMatch::start()
{
    nextWave();
}

void GameMatch::stop()
{
    
}

void GameMatch::nextWave()
{
    if(this->currentWave >= 0 && this->currentWave < this->gameWorld->getMap()->getListWave()->count())
    {
        ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->stop();
    }
    this->currentWave++;
    if( this->currentWave < this->gameWorld->getMap()->getListWave()->count())
    {
        ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->start();
    }
}

bool GameMatch::checkWin()
{
    return false;
}

bool GameMatch::checkLose()
{
    return false;
}

bool GameMatch::checkNextWave()
{
    return false;
}
