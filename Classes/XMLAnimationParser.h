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

USING_NS_CC;
using namespace tinyxml2;

class XMLAnimationParser
{
public:
    static CCAnimation* getAnimationFromXMLNode(XMLElement* xmlElement);
    static AnimationObject* getAnimationObjectFromXMLNode(XMLElement* xmlElement);
};

#endif /* defined(__SampleCocosProject__XMLAnimationParser__) */
