//
//  XMLAnimationParser.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "XMLAnimationParser.h"


CCAnimation* XMLAnimationParser::getAnimationFromXMLNode(tinyxml2::XMLElement *xmlElement)
{
    // Get delay param
    float delay = atof(xmlElement->Attribute("delay"));
    
    // Get frames
    CCArray* frames = new CCArray();

    
    for (XMLElement* element = xmlElement->FirstChildElement("frame"); element; element = element->NextSiblingElement())
    {
        const char* frameName = element->Attribute("name");
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
    frames->autorelease();
    
    return animation;

}

AnimationObject* XMLAnimationParser::getAnimationObjectFromXMLNode(XMLElement *animationXMLElement)
{
    
    AnimationObject *animationObject = new AnimationObject();
    animationObject->retain();
    
    // Get delay param
    float delay = atof(animationXMLElement->Attribute("delay"));
    
    // Get frames
    CCArray* frames = CCArray::create();
        //origin Node
    XMLElement* originXMLElement = animationXMLElement->FirstChildElement("origin");
    
    CCPoint origin;
    origin.x = atof(originXMLElement->Attribute("x"));
    origin.y = atof(originXMLElement->Attribute("y"));
    
    //frame Node
    XMLElement* framelistXMLNode = animationXMLElement->FirstChildElement("framelist");

    
    for (XMLElement* element = framelistXMLNode->FirstChildElement("frame"); element; element = element->NextSiblingElement())
    {
        const char* frameName = element->Attribute("name");
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
    }
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, delay);
  
 

    //
    animationObject->setAnimation(animation);
    animationObject->setOrigin(origin);
    

    
    return animationObject;
    
}