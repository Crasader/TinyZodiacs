//
//  PhysicBodyManager.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#include "GameObjectManager.h"
#include "NormalProjectile.h"

static GameObjectManager* instance = NULL;

GameObjectManager::GameObjectManager()
{
    this->listObjectRemoved = CCArray::create();
    this->listObjectRemoved->retain();
    
    this->listGameObject = CCArray::create();
    this->listGameObject->retain();
}

GameObjectManager::~GameObjectManager()
{
    CC_SAFE_RELEASE(this->listObjectRemoved);
    CC_SAFE_RELEASE(this->listGameObject);
}

bool GameObjectManager::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    this->scheduleUpdate();
    return true;
}

void GameObjectManager::release()
{
//    if(getInstance() != NULL)
//    {
//        delete getInstance();
//    }
}

GameObjectManager* GameObjectManager::getInstance()
{
    if(instance == NULL)
    {
        instance = GameObjectManager::create();
    }
    
    return instance;
}

void GameObjectManager::addObjectRemoved(GameObject *body)
{
    this->listObjectRemoved->addObject(body);
    removeGameObject(body);
}

void GameObjectManager::update(float dt)
{
    CCObject* object;
    CCARRAY_FOREACH(this->listGameObject, object)
    {
        ((GameObject*)object)->update(dt);
    }
    
    this->listObjectRemoved->removeAllObjects();
}

void GameObjectManager::addGameObject(GameObject* object)
{
    this->listGameObject->addObject(object);
}

void GameObjectManager::removeGameObject(GameObject* object)
{
    if(this->listGameObject->indexOfObject(object) != CC_INVALID_INDEX)
    {
        this->listGameObject->removeObject(object);
    }
}

void GameObjectManager::removeAllGameObject()
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listGameObject, object)
    {
        ((GameObject*)object)->destroy();
    }
}


void GameObjectManager::BeginContact(b2Contact *contact)
{
    
    if(contact->GetFixtureA()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
}

void GameObjectManager::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInEndContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()/*->GetBody()*/->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInEndContact(holderData, collisionData,contact);
    }
}


void GameObjectManager::checkCollisionDataInBeginContact(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact)
{
    if(holderData == NULL || holderData->data == NULL)
    {
        return;
    }
    switch (holderData->gameObjectID) {
        case HERO:
            ((Hero*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case MONSTER:
            ((Monster*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case MAP_OBJECT:
            ((MapObject*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case TOWER:
            ((Tower*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case ITEM:
            ((Item*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
            break;
        case PROJECTILE_OBJECT:
            ((NormalProjectile*)holderData->data)->checkCollisionDataInBeginContact(holderData, collisionData, contact);
        default:
            break;
    }
    
    
}

void GameObjectManager::checkCollisionDataInEndContact(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact)
{
    if(holderData == NULL || holderData->data == NULL)
    {
        return;
    }
    
    switch (holderData->bodyId) {
        case PROJECTILE:
        {
            void* pData = holderData->data;
            NormalProjectile* projectile = (NormalProjectile *)pData;
            if(projectile != NULL)
            {
                projectile->checkCollisionDataInEndContact(holderData, collisionData, contact);
            }
            break;
        }
        default:
            break;
    }
    
    ///
    switch (holderData->gameObjectID) {
        case HERO:
            ((Hero*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
        case MONSTER:
            ((Monster*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
        case MAP_OBJECT:
            ((MapObject*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
        case TOWER:
            ((Tower*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
        case ITEM:
            ((Item*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;
            
        default:
            break;
    }
    
}