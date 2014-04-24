//
//  XMLAnimationParser.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "XMLAnimationParser.h"
#include "MapObject.h"



CCAnimation* XMLAnimationParser::getAnimationFromXMLNode(tinyxml2::XMLElement *animationXMLElement)
{
    // Get delay param
    float delay = atof(animationXMLElement->Attribute(DELAY_TAG));
    
    
    XMLElement* framelistXMLNode = animationXMLElement->FirstChildElement(FRAME_LIST_TAG);

    
    // Get frames
    CCArray* frames = CCArray::create();
    
    for (XMLElement* element = animationXMLElement->FirstChildElement(FRAME_TAG); element; element = element->NextSiblingElement())
    {
        const char* frameName = element->Attribute(NAME_TAG);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
    
    return animation;
    
}

AnimationObject* XMLAnimationParser::getAnimationObjectFromXMLNode(XMLElement *animationXMLElement)
{
    
    AnimationObject *animationObject = new AnimationObject();
    animationObject->retain();
    
    // Get delay param
    float delay = atof(animationXMLElement->Attribute(DELAY_TAG));
    
    // Get frames
    CCArray* frames = CCArray::create();
    //origin Node
  //  XMLElement* originXMLElement = animationXMLElement->FirstChildElement("origin");
    
//    CCPoint origin;
//    origin.x = atof(originXMLElement->Attribute("x"));
//    origin.y = atof(originXMLElement->Attribute("y"));
    
    //frame Node
    XMLElement* framelistXMLNode = animationXMLElement->FirstChildElement(FRAME_LIST_TAG);
    
    
    for (XMLElement* element = framelistXMLNode->FirstChildElement(FRAME_TAG); element; element = element->NextSiblingElement())
    {
        const char* frameName = element->Attribute(NAME_TAG);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
    
    
    
    //
    animationObject->setAnimation(animation);
 //   animationObject->setOrigin(origin);
    
    
    
    return animationObject;
    
}

