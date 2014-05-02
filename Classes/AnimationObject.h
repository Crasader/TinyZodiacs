//
//  AnimationObject.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/11/14.
//
//

#ifndef __SampleCocosProject__AnimationObject__
#define __SampleCocosProject__AnimationObject__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class AnimationObject: public cocos2d::CCObject
{
private:
protected:
public:
   
    CC_SYNTHESIZE_RETAIN(CCAnimation*, animation, Animation);
    CC_SYNTHESIZE(CCPoint, origin, Origin);
    
    AnimationObject(CCAnimation* animation, CCPoint origin);
    AnimationObject();
    ~AnimationObject();
};

#endif /* defined(__SampleCocosProject__AnimationObject__) */
