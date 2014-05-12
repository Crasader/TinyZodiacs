//
//  PhysicBodyManager.h
//  TinyZodiacs
//
//  Created by Nhut on 3/21/14.
//
//

#ifndef __TinyZodiacs__PhysicBodyManager__
#define __TinyZodiacs__PhysicBodyManager__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameObject.h"

USING_NS_CC;
class GameObjectManager: public CCNode
{
private:
    CC_SYNTHESIZE(CCArray*, listObjectRemoved, ListObjectRemoved);
    CC_SYNTHESIZE(CCArray*, listGameObject, ListGameObject);
protected:
    GameObjectManager();
    ~GameObjectManager();
public:
    static GameObjectManager* getInstance();
    
    virtual bool init();
    virtual void update(float dt);
    
    void addObjectRemoved(GameObject* object);
    void addObjectUpdate(GameObject* object);

    void removedObjectUpdate(GameObject* object);
    
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
    
    void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);

    static void release();
   
    CREATE_FUNC(GameObjectManager);
};
#endif /* defined(__TinyZodiacs__PhysicBodyManager__) */
