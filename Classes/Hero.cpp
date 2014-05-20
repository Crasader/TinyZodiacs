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

void Hero::onCreate()
{
    
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
    item->prepareToPickedUpAndDestroy(this->sprite);
}

void Hero::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    Character::checkCollisionDataInBeginContact(holderData, collisionData, contact);
    
    if(holderData->Data == this)
    {
        //        PhysicData* physicData = NULL;
        //        if(isSideA)
        //        {
        //            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        //        }
        //        else
        //        {
        //            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        //        }
        
        if( collisionData != NULL)
        {
            
            switch (holderData->BodyId)
            {
                case CHARACTER_FOOT_SENSOR:
                    break;
                case CHARACTER_BODY:
                {
                    if(collisionData->BodyId == GAME_ITEM)
                    {
                        contact->SetEnabled(false);
                        Item* item = static_cast<Item*>(collisionData->Data);
                        if(item->getCanBePickedUp())
                        {
                            this->pickUp(item);
                        }
                        
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
