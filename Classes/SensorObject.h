//
//  SensorObject.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/21/14.
//
//

#ifndef __TinyZodiacs__SensorObject__
#define __TinyZodiacs__SensorObject__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameObject.h"

USING_NS_CC;

class SensorObject: public GameObject
{
private:
    
protected:
    void checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA);
    void checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA);

public:
    CC_SYNTHESIZE(float, jumpHeight, JumpHeight);
    CC_SYNTHESIZE(float, moveSpeed, MoveSpeed);
    CC_SYNTHESIZE(bool, mustStop, MustStop);
    CC_SYNTHESIZE(bool, isBack, IsBack);
    vector<int> listLaneID;
    
    SensorObject();
    ~SensorObject();
    virtual bool init();
    virtual void update(float dt);
    
    bool checkValidLaneID(int landID);
 
    CREATE_FUNC(SensorObject);
};


#endif /* defined(__TinyZodiacs__SensorObject__) */
