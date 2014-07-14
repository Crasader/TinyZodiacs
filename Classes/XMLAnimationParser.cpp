//
//  XMLAnimationParser.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "XMLAnimationParser.h"
#include "MapObject.h"

//CCAnimation* XMLAnimationParser::getAnimationFromXMLNode(tinyxml2::XMLElement *animationXMLElement)
//{
//    // Get delay param
//    float delay = atof(animationXMLElement->Attribute(DELAY_TAG));
//
//
//    XMLElement* framelistXMLNode = animationXMLElement->FirstChildElement(FRAME_LIST_TAG);
//
//
//    // Get frames
//    CCArray* frames = CCArray::create();
//
//    for (XMLElement* element = animationXMLElement->FirstChildElement(FRAME_TAG); element; element = element->NextSiblingElement())
//    {
//        const char* frameName = element->Attribute(NAME_TAG);
//        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
//    }
//
//    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
//
//    return animation;
//
//}

AnimationObject* XMLAnimationParser::getAnimationObjectFromXMLNode(XMLElement *animationXMLElement)
{
    
    AnimationObject *animationObject = new AnimationObject();
    animationObject->retain();
    
    // Get delay param
    float delay = atof(animationXMLElement->Attribute(ATTRIBUTE_DELAY));
    unsigned int loop = 1;
    if(animationXMLElement->Attribute(ATTRIBUTE_IS_LOOP) != NULL)
    {
        if(strcasecmp(animationXMLElement->Attribute(ATTRIBUTE_IS_LOOP), "infinity") == 0)
        {
            loop = INFINITY;
        }
        else
        {
            loop = atoi(animationXMLElement->Attribute(ATTRIBUTE_IS_LOOP));
        }
    }
    else
    {
        loop = 1;
    }
    
    // Get frames
    CCArray* frames = CCArray::create();
    
    XMLElement* framelistXMLNode = animationXMLElement->FirstChildElement(TAG_FRAME_LIST);
    
    vector<string> listFrameName;
    
    for (XMLElement* element = framelistXMLNode->FirstChildElement(TAG_FRAME); element; element = element->NextSiblingElement())
    {
        const char* frameName = element->Attribute(ATTRIBUTE_NAME);
        //frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
        listFrameName.push_back(frameName);
    }
    
   // CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
  //  animation->setLoops(loop);
    
 //   animationObject->setAnimation(animation);
    animationObject->setListFrameName(listFrameName);
    
    animationObject->setLoops(loop);
    animationObject->setDelayPerUnit(delay);
    return animationObject;
}

