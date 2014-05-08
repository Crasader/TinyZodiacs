//
//  Monster.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "Monster.h"
#include "SensorObject.h"
#include "Util.h"
#include "MonsterFactory.h"
#include "GameObjectManager.h"
#include "HealthPointEffect.h"
#include "EffectManager.h"
#include "AnimationEffect.h"

Monster::Monster()
{
    isStopMove = false;
    this->landing = 0;
}

Monster::~Monster()
{
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    
    EffectManager::getInstance()->runEffect(effect, this->getPositionInPixel());
}

bool Monster::init()
{
    if (!Character::init()) {
        return false;
    }
    this->sprite = CCSprite::createWithSpriteFrameName("cat_idle_1.png");
    return true;
}

void Monster::update(float dt)
{
    
    Character::update(dt);
    if(!isStopMove)
    {
        this->move(this->direction);
    }
    
}


void Monster::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    Character::checkCollisionDataInBeginContact(data, contact, isSideA);
    
    if(data->Data == this)
    {
        PhysicData* physicData = NULL;
        if(isSideA)
        {
            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        }
        if(physicData != NULL)
        {
            switch (physicData->Id) {
                case MAP_SENSOR:
                {
                    if(data->Id == CHARACTER_FOOT_SENSOR)
                    {
                        
                        SensorObject* sensorObject = static_cast<SensorObject*>(physicData->Data);
                        if(sensorObject->checkValidLaneID(this->laneID))
                        {
                            // cung huong
                            if(this->direction == sensorObject->getDirection())
                            {
                                doAction(sensorObject);
                            }
                            else if(sensorObject->getIsBack())
                            {
                                doAction(sensorObject);
                            }
                            
                        }
                    }
                }
                    break;
                    
                case MAP_BASE:
                {
                    if(data->Id == CHARACTER_FOOT_SENSOR)
                    {
                        MapObject* mapObject = static_cast<MapObject*>(physicData->Data);
                        if(!Util::bodiesArePassingThrough(this->body, mapObject->getBody()))
                        {
                             this->isStopMove = false;
                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Monster::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    Character::checkCollisionDataInEndContact(data, contact, isSideA);
    if(data->Data == this)
    {
        PhysicData* physicData = NULL;
        if(isSideA)
        {
            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        }
        
        if(physicData != NULL)
        {
            switch (physicData->Id) {
                case MAP_SENSOR:
                {
                    //this->isStopMove = false;
                }
                    break;
                default:
                    break;
            }
        }
    }
    
}


void Monster::doAction(SensorObject* sensorObject)
{
   
    if(sensorObject->getMustStop())
    {
        isStopMove = true;
        this->stopMove();
    }
    if(sensorObject->getMoveSpeed() > 0)
    {
        this->move(sensorObject->getDirection(), sensorObject->getMoveSpeed());
    }
    if(sensorObject->getJumpHeight() > 0)
    {
        this->jump(sensorObject->getJumpHeight());
    }
}

void Monster::notifyByEffect(CCObject* effect)
{
    Character::notifyByEffect(effect);
    if(this->getcharacterData().getHealth() <= 0)
    {
        GameObjectManager::getInstance()->addObjectRemoved(this);
    }
}

void Monster::setPhysicGroup(uint16 group)
{
    Character::setPhysicGroup(group);
    this->setSensorGroup(group);
}

void Monster::setSensorGroup(uint16 group)
{
    for (b2Fixture* f = this->sensor->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits = group;
            switch (group) {
                case GROUP_A:
                case GROUP_HERO_A:
                case GROUP_TOWER_A:
                    filter.maskBits = GROUP_TOWER_B|GROUP_B|GROUP_HERO_B|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_B:
                case GROUP_HERO_B:
                case GROUP_TOWER_B:
                    filter.maskBits = GROUP_TOWER_A|GROUP_A|GROUP_HERO_A|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_NEUTRUAL:
                    filter.maskBits = GROUP_A | GROUP_B | GROUP_HERO_A | GROUP_HERO_B;
                    break;
                    
                default:
                    break;
            }
            f->SetFilterData(filter);
        }
    }
}