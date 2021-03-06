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
    this->listObjectRemoved->release();
   this->listGameObject->release();
}

bool GameObjectManager::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
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
    instance->listObjectRemoved->addObject(body);
    removeGameObject(body);
}

void GameObjectManager::update(float dt)
{
    CCObject* object;
    CCARRAY_FOREACH(instance->listGameObject, object)
    {
        GameObject* gameObject = static_cast<GameObject*>(object);
        if(gameObject)
        {
            gameObject->update(dt);
        }
    }
    instance->listObjectRemoved->removeAllObjects();
}

void GameObjectManager::addGameObject(GameObject* object)
{
    instance->listGameObject->addObject(object);
}

void GameObjectManager::removeGameObject(GameObject* object)
{
    if(instance->listGameObject->indexOfObject(object) != CC_INVALID_INDEX)
    {
        instance->listGameObject->removeObject(object);
    }
}

void GameObjectManager::removeAllGameObject()
{
    CCArray* copyArray = CCArray::create();
    copyArray->addObjectsFromArray(instance->listGameObject);
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(copyArray, object)
    {
        GameObject* gameObject = static_cast<GameObject*>(object);
        gameObject->destroy();
    }
    instance->listObjectRemoved->removeAllObjects();
}
void GameObjectManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInPreSolve(holderData, collisionData,contact,oldManifold);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInPreSolve(holderData, collisionData,contact,oldManifold);
    }

}

void GameObjectManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInPostSolve(holderData, collisionData,contact,impulse);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInPostSolve(holderData, collisionData,contact,impulse);
    }

}
void GameObjectManager::BeginContact(b2Contact *contact)
{
    
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInBeginContact(holderData, collisionData,contact);
    }
}

void GameObjectManager::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetUserData() != NULL)
    {
        PhysicData* holderData = (PhysicData*)contact->GetFixtureA()/*->GetBody()*/->GetUserData();
        PhysicData* collisionData = (PhysicData*)contact->GetFixtureB()/*->GetBody()*/->GetUserData();
        
        checkCollisionDataInEndContact(holderData, collisionData,contact);
    }
    
    if(contact->GetFixtureB()->GetUserData() != NULL)
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
        case GOLD_ITEM:
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

        case GOLD_ITEM:
            ((Item*)holderData->data)->checkCollisionDataInEndContact(holderData, collisionData, contact);
            break;

        default:
            break;
    }
    
}

void GameObjectManager::checkCollisionDataInPreSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2Manifold* oldManifold)
{
    if(holderData == NULL || holderData->data == NULL)
    {
        return;
    }
    
    switch (holderData->gameObjectID) {
        case HERO:
            ((Hero*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
        case MONSTER:
            ((Monster*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
        case MAP_OBJECT:
            ((MapObject*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
        case TOWER:
            ((Tower*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
        case ITEM:
            ((Item*)holderData->data)->checkCollisionDataInPreSolve(holderData, collisionData, contact, oldManifold);
            break;
            
        default:
            break;
    }
    
}
void GameObjectManager::checkCollisionDataInPostSolve(PhysicData* holderData , PhysicData* collisionData, b2Contact *contact, const b2ContactImpulse* impulse)
{
    if(holderData == NULL || holderData->data == NULL)
    {
        return;
    }
    
    switch (holderData->gameObjectID) {
        case HERO:
            ((Hero*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        case MONSTER:
            ((Monster*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        case MAP_OBJECT:
            ((MapObject*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        case SKILL_OBJECT:
            ((AbstractSkill*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        case TOWER:
            ((Tower*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        case ITEM:
            ((Item*)holderData->data)->checkCollisionDataInPostSolve(holderData, collisionData, contact, impulse);
            break;
        default:
            break;
    }

}