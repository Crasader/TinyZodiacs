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
}

bool GameObjectLayer::init()
{
    
    if(!CCLayer::init())
    {
        return false;
    }

    GameBackgroundLayer* backgroundLayer = GameBackgroundLayer::create();
    
    MapCreator* mapCreator = new MapCreator();
    
    map = mapCreator->createMap("dsdsd");
    map->attachAllMapObject();
   
    this->addChild(map,1);
    
    delete mapCreator;

    map->setFollowCharacter(true);

    this->scheduleUpdate();
  //  map->addChild(backgroundLayer,0);
    return true;
}

void GameObjectLayer::draw()
{
}

void GameObjectLayer::update(float dt)
{
    map->update(dt);
}

void GameObjectLayer::MoveSprite(float x, float y)
{
   
}

void GameObjectLayer::MoveSpriteUp()
{

    this->map->getCharacter()->jump();
    
}

void GameObjectLayer::MoveSpriteDown()
{
    this->map->getCharacter()->stopMove();
}

void GameObjectLayer::MoveSpriteLeft()
{
    this->map->getCharacter()->move(LEFT);
}

void GameObjectLayer::MoveSpriteRight()
{
     this->map->getCharacter()->move(RIGHT);
}

void GameObjectLayer::Attack()
{
    this->map->getCharacter()->attack();
}
