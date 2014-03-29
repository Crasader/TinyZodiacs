//
//  Map.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#ifndef __SampleCocosProject__Map__
#define __SampleCocosProject__Map__

#include <iostream>
#include "cocos2d.h"
#include "MapObject.h"
#include "Box2D/Box2D.h"
#include "Character.h"


class Map: public cocos2d::CCNode
{
private:

    cocos2d::CCArray* listMapObject;
    
protected:
public:
    CC_SYNTHESIZE(float, width, Width);
    CC_SYNTHESIZE(float, height, Height);
    CC_SYNTHESIZE(CCParallaxNode*, parallaxBackground, ParallaxBackground);
  
    
    
    Map();
    virtual ~Map();
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(Map);
    
    void addMapObject(MapObject* mapObject);
    void attachAllMapObject();
    void addParallaxBackground(CCParallaxNode* parallaxBackground);
    void addParallaxForeground(CCParallaxNode* parallaxForeground);

    
};

#endif /* defined(__SampleCocosProject__Map__) */
