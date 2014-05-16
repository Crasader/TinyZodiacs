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
    if(getInstance() != NULL)
    {
        delete getInstance();
    }
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
  //  if(this->listGameObject->indexOfObject(object) != CC_INVALID_INDEX)
    {
        this->listGameObject->removeObject(object);
    }
}

void GameObjectManager::BeginContact(b2Contact *contact)
{
    
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, false);
    }
}

void GameObjectManager::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, false);
    }
}


void GameObjectManager::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data == NULL || data->Data == NULL)
    {
        return;
    }
    
    switch (data->BodyId)
    {
        case PROJECTILE:
        {
            void* pData = data->Data;
            NormalProjectile* projectile = static_cast<NormalProjectile*>(pData);
            if(projectile != NULL)
            {
                projectile->checkCollisionDataInBeginContact(data, contact, isSideA);
            }
            break;
        }
        default:
       
            break;
    }
    
    ///
    switch (data->GameObjectID) {
        case MONSTER:
            ((Monster*)data->Data)->checkCollisionDataInBeginContact(data,contact,isSideA);
            break;
        case MAP_OBJECT:
            ((MapObject*)data->Data)->checkCollisionDataInBeginContact(data,contact,isSideA);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)data->Data)->checkCollisionDataInBeginContact(data,contact,isSideA);
            break;
        case TOWER:
            ((Tower*)data->Data)->checkCollisionDataInBeginContact(data,contact,isSideA);
            break;
        default:
            break;
    }

    
}

void GameObjectManager::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data == NULL || data->Data == NULL)
    {
        return;
    }
    
    switch (data->BodyId) {
        case PROJECTILE:
        {
            void* pData = data->Data;
            NormalProjectile* projectile = (NormalProjectile *)pData;
            if(projectile != NULL)
            {
                projectile->checkCollisionDataInEndContact(data, contact, isSideA);
            }
            break;
        }
        default:
            break;
    }
 
    ///
    switch (data->GameObjectID) {
        case MONSTER:
            ((Monster*)data->Data)->checkCollisionDataInEndContact(data,contact,isSideA);
            break;
        case MAP_OBJECT:
            ((MapObject*)data->Data)->checkCollisionDataInEndContact(data,contact,isSideA);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)data->Data)->checkCollisionDataInEndContact(data,contact,isSideA);
            break;
        case TOWER:
            ((Tower*)data->Data)->checkCollisionDataInEndContact(data,contact,isSideA);
            break;
        default:
            break;
    }

}