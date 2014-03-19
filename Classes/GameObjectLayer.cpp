//
//  GameObjectLayer.cpp
//  SampleCocosProject
//
//  Created by Nguy���n H��a Ph��t on 1/9/14.
//
//

#include "GameObjectLayer.h"
#include "GameBackgroundLayer.h"
#include "Box2D/Box2D.h"
#include "GB2ShapeCache-x.h"
#include "ObjectFactory.h"
#include "GLES-Render.h"
#include "MapCreator.h"


USING_NS_CC;

GameObjectLayer::GameObjectLayer()
{
    
}

GameObjectLayer::~GameObjectLayer()
{
    delete this->characterActionEngine;
}

bool GameObjectLayer::init()
{
    
    if(!CCLayer::init())
    {
        return false;
    }

      
    this->gameWorld = new GameWorld(0,0,2000,2000);
    this->addChild(gameWorld);
    
    this->characterActionEngine = new CharacterActionEngine(this->gameWorld->getCharacter());
    
    return true;
}

void GameObjectLayer::draw()
{
}

void GameObjectLayer::update(float dt)
{
     // this->gameWorld->update(dt);
}

void GameObjectLayer::MoveSprite(float x, float y)
{
   
}

void GameObjectLayer::MoveSpriteUp()
{

//  this->gameWorld->getCharacter()->jump();
    this->characterActionEngine->jump();
}

void GameObjectLayer::MoveSpriteDown()
{
//    this->gameWorld->getCharacter()->stopMove();
    this->characterActionEngine->stopMoveAction();
}

void GameObjectLayer::MoveSpriteLeft()
{
//   this->gameWorld->getCharacter()->move(LEFT);
    this->characterActionEngine->moveLeft();
}

void GameObjectLayer::MoveSpriteRight()
{
//    this->gameWorld->getCharacter()->move(RIGHT);
    this->characterActionEngine->moveRight();
}

void GameObjectLayer::Attack()
{
//    this->gameWorld->getCharacter()->attack();
    this->characterActionEngine->attack();
}
