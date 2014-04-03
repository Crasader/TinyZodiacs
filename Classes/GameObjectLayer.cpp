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
    CC_SAFE_RELEASE_NULL(this->gameWorld);
    delete this->characterActionEngine;
}

bool GameObjectLayer::init()
{
    
    if(!CCLayer::init())
    {
        return false;
    }
      
    this->gameWorld = GameWorld::create();
    
    this->addChild(gameWorld);
    
    this->characterActionEngine = new CharacterActionEngine(this->gameWorld->getCharacter());
    
    this->scheduleUpdate();
    
    return true;
}

void GameObjectLayer::draw()
{
}

void GameObjectLayer::update(float dt)
{
      this->gameWorld->update(dt);
}

void GameObjectLayer::MoveSprite(float x, float y)
{
   
}

void GameObjectLayer::MoveSpriteUp()
{
   // CC_SAFE_RELEASE(this->gameWorld);
 // this->gameWorld->getCharacter()->jump();
    this->characterActionEngine->jump();
    
//CC_SAFE_RELEASE(this->gameWorld);
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

void GameObjectLayer::Skill1()
{
    //    this->gameWorld->getCharacter()->attack();
    this->characterActionEngine->skill1();
}

void GameObjectLayer::Skill2()
{
    //    this->gameWorld->getCharacter()->attack();
    this->characterActionEngine->skill2();
}
