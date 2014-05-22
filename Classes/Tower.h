//
//  Tower.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/21/14.
//
//

#ifndef __TinyZodiacs__Tower__
#define __TinyZodiacs__Tower__

#include <iostream>
#include "Character.h"
#include "Box2D/Box2D.h"
#include "PhysicConstants.h"

class Tower: public Character
{
private:
    CCArray* listTarget;

    
    b2Vec2 getStartPoint(b2Body* body, JointDef jointDef);
protected:
    CC_SYNTHESIZE(b2Fixture*, sensor, Sensor);
    
    void createSensor();
    void  setSensorGroup(uint16 group);
    
    void checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    void checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact);
    
    void aimTarget();
    
    virtual uint16  getCorrectGroup(Group group);
    virtual void setPhysicGroup(uint16 group);

public:
    Tower();
    ~Tower();
    
    virtual bool init();
    void update(float dt);
    
    virtual void setSkin(b2Body* body,cocos2d::CCSprite* sprite);
    virtual void onCreate();
    virtual void destroy();
    
    virtual void attach(Observer* observer);
    virtual void detach(Observer* observer);
    virtual void notifyToDestroy();

    virtual void flipDirection(Direction direction);
    
    void setSensor(const char* bodyId);
    
    CREATE_FUNC(Tower);
};
#endif /* defined(__TinyZodiacs__Tower__) */
