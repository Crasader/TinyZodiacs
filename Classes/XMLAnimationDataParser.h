//
//  XMLAnimationDataParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 5/31/14.
//
//

#ifndef __TinyZodiacs__XMLAnimationDataParser__
#define __TinyZodiacs__XMLAnimationDataParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "AnimationData.h"

USING_NS_CC;
using namespace tinyxml2;

#define TAG_ANIMATION_ID "animation"

class XMLAnimationDataParser
{
public:
    static std::string readAnimationId(const XMLElement* root);
    static int readAnimationLayerIndex(const XMLElement* root);
    static float readMinRotation(const XMLElement* root);
    static float readMaxRotation(const XMLElement* root);
    static float readMinScale(const XMLElement* root);
    static float readMaxScale(const XMLElement* root);
    static int readRepeatTimes(const XMLElement* root);
    
    static AnimationData parseData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLAnimationDataParser__) */
