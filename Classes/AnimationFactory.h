//
//  AnimationFactory.h
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#ifndef __SampleCocosProject__AnimationFactory__
#define __SampleCocosProject__AnimationFactory__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"

#define OBJECT_ANIMATION

USING_NS_CC;

class AnimationFactory
{
private:
 
    cocos2d::CCDictionary* animationDictionary;
public:
    AnimationFactory();
    virtual ~AnimationFactory();

    static AnimationFactory* getSharedFactory();
    bool loadXMLAnimation();
    bool loadXMLAnimationByNameFile(const char* filename);
    cocos2d::CCAnimation* getAnimationByName(const char* keyAnimation);
    AnimationObject* getAnimationObjectByName(const char* keyAnimation);
};

#endif /* defined(__SampleCocosProject__AnimationFactory__) */
