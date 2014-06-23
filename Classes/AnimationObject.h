//
//  AnimationObject.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/11/14.
//
//

#ifndef __SampleCocosProject__AnimationObject__
#define __SampleCocosProject__AnimationObject__

class AnimationObject;

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class AnimationObject: public cocos2d::CCObject
{
private:
    CC_SYNTHESIZE(vector<string>, listFrameName, ListFrameName);
    CC_SYNTHESIZE_RETAIN(CCAnimation*, animation, Animation);
    CC_SYNTHESIZE(CCPoint, origin, Origin);
    CC_SYNTHESIZE(unsigned int, loops, Loops);
    CC_SYNTHESIZE(float, delayPerUnit, DelayPerUnit);
protected:
public:
    
    AnimationObject(CCAnimation* animation, CCPoint origin);
    AnimationObject();
    ~AnimationObject();
};

#endif /* defined(__SampleCocosProject__AnimationObject__) */
