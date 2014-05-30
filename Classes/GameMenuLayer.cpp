//
//  GameMenuLayer.cpp
//  SampleCocosProject
//
//  Created by ; Hòa Phát on 1/9/14.
//
//

#include "GameMenuLayer.h"
#include "GameBackgroundLayer.h"
#include "GameObjectLayer.h"
#include "ControllerLayer.h"
#include "HealthPointEffect.h"
#include "EffectManager.h"

USING_NS_CC;

bool GameMenuLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    mlayer = ControllerLayer::create(this);
    mlayer->setLeftButtonEventHadler(this);
    mlayer->setRightButtonEventHadler(this);
    mlayer->setJumpButtonEventHadler(this);
    mlayer->setAtkButtonEventHadler(this);
    mlayer->setSkill1ButtonEventHadler(this);
    mlayer->setSkill2ButtonEventHadler(this);
    
    
    this->addChild(mlayer, 1);
    
    this->setTouchEnabled(true);
    
    
    label = CCLabelTTF::create("0", "Arial", 30);
    label->setPosition(ccp(500,500));
    label->setAnchorPoint(ccp(0,0));
    
    monsterCount = CCLabelTTF::create("0", "Arial", 30);
    monsterCount->setPosition(ccp(800,500));
    monsterCount->setAnchorPoint(ccp(0,0));
    
    
    this->addChild(label);
    this->addChild(monsterCount);
    
    this->scheduleUpdate();
    
    
    //CONTROLLER
    
    
    //this->addChild(mlayer, 1);
    
    
    this->setTouchEnabled(true);
    
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    
    return true;
    
    
    
    
}

void GameMenuLayer::update(float dt)
{
   }


void GameMenuLayer::touchBegan(void* sender ,CCSet* pTouches, CCEvent* event)
{
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_JUMP);
        
    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_1);
    }
    else if(id.compare(SKILL_1_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_2);
    }
    else if(id.compare(SKILL_2_BTN_ID) == 0)
    {
        
    }
}
void GameMenuLayer::touchHold(void* sender ,CCSet* pTouches, CCEvent* event)
{
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_LEFT);
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
        
        
    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
        
        
    }
}
void GameMenuLayer::touchEnded(void* sender ,CCSet* pTouches, CCEvent* event)
{
    ;
    std::string id = ((UIObject *)sender)->getID();
    if(id.compare(LEFT_BTN_ID) == 0)
    {
        
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
        
    }
    else if(id.compare(RIGHT_BTN_ID) == 0)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
        
        
    }
    else if(id.compare(JUMP_BTN_ID) == 0)
    {
    }
    else if(id.compare(ATK_BTN_ID) == 0)
    {
    }
}

void GameMenuLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event)
{
    //    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    //    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()) ;
    //
    //
    //    label->setString(CCString::createWithFormat("%0.2f-%0.2f",touchPoint.x,touchPoint.y)->getCString());
}

bool GameMenuLayer::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    switch (commandID)
    {
        case DISABLE_BUTTON_ATTACK:
            mlayer->getAtkButtonSprite()->changeState(DISABLE);
            break;
        case DISPLAY_MONSTER_COUNT:
        {
            int* count = static_cast<int*>(data);
            monsterCount->setString(CCString::createWithFormat("%d",*count)->getCString());
        }
            break;
        case DISPLAY_NEW_WAVE:
        {
            int* waveNumber = static_cast<int*>(data);
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            CCLabelTTF* labelStyle = CCLabelTTF::create("", "Marker Felt", 150);
            labelStyle->setOpacity(100);
            
            TextShowEffect* effect = TextShowEffect::create();
            effect->setContent(CCString::createWithFormat("Wave %d", *waveNumber)->getCString());
            effect->setLabelStyle(labelStyle);
            
            EffectManager::getInstance()->runEffect(effect, ccp(size.width/2, size.height/2),this);
            
            delete waveNumber;
        }
            break;
        case DISPLAY_WORLD_COORDINATE:
        {
            CCPoint* point = static_cast<CCPoint*>(data);
         
            label->setString(CCString::createWithFormat("%f - %f",point->x,point->y)->getCString());
        }
            
        default:
            break;
    }
    return true;
}

bool GameMenuLayer::removeSubController(Controller* controller)
{
    Controller::removeSubController(controller);
    return true;
}

