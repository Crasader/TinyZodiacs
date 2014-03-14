//
//  AnimationObject.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/11/14.
//
//

#include "AnimationObject.h"

USING_NS_CC;


AnimationObject::AnimationObject()
{
    this->animation = NULL;
    origin.setPoint(0, 0);
}

AnimationObject::AnimationObject(CCAnimation* animation, CCPoint origin)
{
    this->animation = animation;
    this->origin = origin;
}

AnimationObject::~AnimationObject()
{
    this->animation->release();
}


