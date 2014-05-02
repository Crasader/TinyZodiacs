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
#include <string.h>

USING_NS_CC;

#define TAG_OBJECT_ANIMATION_TAG "object_animation"
#define ATTRIBUTE_OBJECT_ANIMATION_PLIST_NAME "plist_name"
#define ATTRIBUTE_OBJECT_ANIMATION_IMAGE_NAME "image_name"

#define TAG_ANIMATION "animation"
#define ATTRIBUTE_NAME "name"
#define ATTRIBUTE_DELAY "delay"
#define ATTRIBUTE_IS_LOOP "loop"
#define TAG_FRAME "frame"
#define TAG_FRAME_LIST "framelist"

using namespace tinyxml2;

class XMLAnimationParser
{
public:
 //   static CCAnimation* getAnimationFromXMLNode(XMLElement* xmlElement);
    static AnimationObject* getAnimationObjectFromXMLNode(XMLElement* xmlElement);

};

#endif /* defined(__SampleCocosProject__XMLAnimationParser__) */
