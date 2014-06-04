//
//  Hero.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "Hero.h"

Hero::Hero()
{
    this->gameObjectID = HERO;
}

bool Hero::init()
{
    if(!Character::init())
    {
        return false;
    }
    this->sprite = CCSprite::createWithSpriteFrameName("cat_idle_1.png");
    
    return true;
}



Hero::~Hero()
{
    
}
bool a = false;
void Hero::onCreate()
{
    Character::onCreate();
    
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    //
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_SKILL_0_TEXTURE_SET, new TextureSelector(this->normalAttack->getSkillTextureSelector()));
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_SKILL_1_TEXTURE_SET, new TextureSelector(this->skill1->getSkillTextureSelector()));
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_SKILL_2_TEXTURE_SET, new TextureSelector(this->skill2->getSkillTextureSelector()));
}

uint16  Hero::getCorrectGroup(Group group)
{
    switch (group)
    {
        case A:
            return GROUP_HERO_A;
        case B:
            return GROUP_HERO_B;
        default:
            return GROUP_NEUTRUAL;
    }
}

void Hero::pickUp(Item* item)
{
    if(item->getIsActive())
    {
        item->contact(this);
    }
}

void Hero::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    Character::checkCollisionDataInBeginContact(holderData, collisionData, contact);
    
    if(holderData->data == this)
    {
        if( collisionData != NULL)
        {
            
            switch (holderData->bodyId)
            {
                case CHARACTER_FOOT_SENSOR:
                    break;
                case CHARACTER_BODY:
                {
                    
                    if(collisionData->bodyId == GAME_ITEM)
                    {
                        contact->SetEnabled(false);
                        Item* item = static_cast<Item*>(collisionData->data);
                        this->pickUp(item);
                    }
                    
                }
                    break;
                default:
                    break;
            }
        }
        ///
        
    }
    
    
}

void Hero::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    Character::checkCollisionDataInEndContact(holderData, collisionData, contact);
}

void Hero::attachSpriteTo(CCNode* node)
{
    GameObject::attachSpriteTo(node);
    node->addChild(this->sprite, CHARACTER_LAYER);
}

void Hero::destroy()
{
    Character::destroy();
}

bool Hero::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    
    switch (commandID)
    {
        case HERO_MOVE_LEFT:
            move(LEFT);
            break;
        case HERO_MOVE_RIGHT:
            move(RIGHT);
            break;
        case HERO_MOVE_STOP:
            stopMove();
            break;
        case HERO_MOVE_JUMP:
            jump();
            break;
        case HERO_ATTACK_1:
            attack();
            break;
        case HERO_ATTACK_2:
            useSkill1();
            break;
        default:
            break;
    }
    
    return true;
}

void Hero::update(float dt)
{
    
    Character::update(dt);
    
    //
    //    if(this->normalAttack->getSkillButtonID()!= UNKNOWN && ControllerManager::getInstance()->isRegisteredWith(HERO_CONTROLLER, this));
    //    {
    //        StateCommandData *data = new StateCommandData();
    //        data->controllerId = this->normalAttack->getSkillButtonID();
    //        if(this->normalAttack->getIsExcutable())
    //        {
    //            data->isActive = true;
    //        }
    //        else
    //        {
    //            data->isActive = false;
    //        }
    //        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_STATE, data);
    //    }
    //
    //    if(this->skill1->getSkillButtonID()!= UNKNOWN && ControllerManager::getInstance()->isRegisteredWith(HERO_CONTROLLER, this));
    //    {
    //        StateCommandData *data = new StateCommandData();
    //        data->controllerId = this->skill1->getSkillButtonID();
    //        if(this->skill1->getIsExcutable())
    //        {
    //            CCLOG("a");
    //            data->isActive = true;
    //        }
    //        else
    //        {
    //            data->isActive = false;
    //        }
    //        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_STATE, data);
    //    }
    //
    //    if(this->skill2->getSkillButtonID()!= UNKNOWN && ControllerManager::getInstance()->isRegisteredWith(HERO_CONTROLLER, this));
    //    {
    //        StateCommandData *data = new StateCommandData();
    //        data->controllerId = this->skill2->getSkillButtonID();
    //        if(this->skill2->getIsExcutable())
    //        {
    //            data->isActive = true;
    //        }
    //        else
    //        {
    //            data->isActive = false;
    //        }
    //        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_STATE, data);
    //    }
    
}

void Hero::notifyUIChange(void* data)
{
    StateCommandData* stateCommandData = static_cast<StateCommandData*>(data);
    if(stateCommandData != NULL)
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, CHANGE_STATE, data);
    }
}

