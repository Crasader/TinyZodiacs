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
#include "MonsterFactory.h"
#include "EffectManager.h"
#include "HealthPointEffect.h"

USING_NS_CC;

GameObjectLayer::GameObjectLayer()
{
    
    gameMatch = NULL;
    node = CCNode::create();
    node->retain();
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
    
    gameMatch = GameMatch::create();
    
    this->addChild(gameMatch);
    
    gameMatch->start();
    this->setTouchEnabled(true);
    this->scheduleUpdate();
    
    return true;
}

void GameObjectLayer::draw()
{
}

void GameObjectLayer::update(float dt)
{
    //    this->gameWorld->update(dt);
}

Character* GameObjectLayer::getCharacter()
{
    return this->characterActionEngine->getCharacter();
}

void GameObjectLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()) ;
    
    CCPoint temp =   this->gameMatch->getGameWorld()->convertToNodeSpace(touchPoint);
    
    CCLOG("coord: %0.1f - %0.1f",temp.x,temp.y);
//    node->setPosition(temp);
//    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_WORLD_COORDINATE, new CCPoint(temp));
    //    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,CAMERA_FOLLOW_POINTER,node);
}

void GameObjectLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
    
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()) ;
    
    CCPoint temp =   this->gameMatch->getGameWorld()->convertToNodeSpace(touchPoint);
    node->setPosition(temp);

}

bool GameObjectLayer::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    switch (commandID)
    {
        case CAMERA_FOLLOW_POINTER:
        {
            GameWorld* world = static_cast<GameWorld*>(data);
            if(this->node->getParent() == NULL)
            {
                world->addChild(this->node);
            }
            world->setCameraFollowNode(node);
            
        }
            break;
        default:
            break;
    }
    return true;
}

bool GameObjectLayer::removeSubController(Controller* controller)
{
    Controller::removeSubController(controller);
    return true;
}
