//
//  Observer.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/13/14.
//
//

#ifndef __TinyZodiacs__Observer__
#define __TinyZodiacs__Observer__

class Observer;
#include <iostream>
#include "GameObject.h"
#include "cocos2d.h"

USING_NS_CC;

class GameObject;
class Observer {
    
private:
protected:
public:
    virtual void notifyToDestroy(GameObject* object) = 0;
};

#endif /* defined(__TinyZodiacs__Observer__) */
