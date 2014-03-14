//
//  MapObject.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#ifndef __SampleCocosProject__MapObject__
#define __SampleCocosProject__MapObject__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

class MapObject: public GameObject
{
private:
protected:
public:
    MapObject();
    ~MapObject();
    
     virtual void update(float dt);
};

#endif /* defined(__SampleCocosProject__MapObject__) */
