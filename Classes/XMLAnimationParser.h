//
//  XMLAnimationParser.h
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#ifndef __SampleCocosProject__XMLAnimationParser__
#define __SampleCocosProject__XMLAnimationParser__

#include <iostream>
#include "Cocos2d.h"
#include "AnimationObject.h"
#include "MapObjectDTO.h"
#include "MapDTO.h"

USING_NS_CC;

#define OBJECT_ANIMATION_TAG "object_animation"
#define OBJECT_ANIMATION_PLIST_NAME_TAG "plist_name"
#define OBJECT_ANIMATION_IMAGE_NAME_TAG "plist_name"

#define ANIMATION_TAG "animation"
#define NAME_TAG "name"
#define FRAME_TAG "frame"
#define FRAME_LIST_TAG "framelist"
#define DELAY_TAG "delay"



using namespace tinyxml2;

class XMLAnimationParser
{
public:
    static CCAnimation* getAnimationFromXMLNode(XMLElement* xmlElement);
    static AnimationObject* getAnimationObjectFromXMLNode(XMLElement* xmlElement);

};

#endif /* defined(__SampleCocosProject__XMLAnimationParser__) */
