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
    this->isDead = false;
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
    if(this->skill1Animation != NULL)
    {
        this->skill1Animation->release();
    }
    if(this->skill2Animation != NULL)
    {
        this->skill2Animation->release();
    }
    if(this->ghostAnimation != NULL)
    {
        this->ghostAnimation->release();
    }
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
    node->addChild(this->sprite,CHARACTER_LAYER);
}

void Hero::destroy()
{
   // Character::destroy();
    
    ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
    dead();
    //ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISABLE_BUTTON_ATTACK);
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
    if(this->isDead == false)
    {
        Character::update(dt);
    }
    
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

void Hero::revive()
{
    this->isDead = false;
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    this->sprite->setVisible(true);
    this->body->SetActive(true);
    
    setcharacterData(this->originCharacterData);
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->setVisible(true);
        this->gameObjectView->notifyChange();
    }
  
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, VISIBLE_ALL_HERO_CONTROLLER);
    setPositionInPixel(ccp(122,780));
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    EffectManager::getInstance()->runEffect(effect, getPositionInPixel());
    this->body->SetLinearVelocity(b2Vec2(0,0));
}

void Hero::dead()
{
    isDead = true;
    ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
    this->sprite->setVisible(false);
    this->body->SetActive(false);
    if(this->gameObjectView != NULL)
    {
        this->gameObjectView->setVisible(false);
    }
    ScheduleManager::getInstance()->scheduleFunction(CCCallFunc::create(this, callfunc_selector(Hero::revive)), NULL, 5, 1);
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    EffectManager::getInstance()->runEffect(effect, getPositionInPixel());
    
    ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, INVISIBLE_ALL_HERO_CONTROLLER);
     this->body->SetLinearVelocity(b2Vec2(0,0));
    
}