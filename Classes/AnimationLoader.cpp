//
//  AnimationFactory.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "AnimationLoader.h"
#include "XMLAnimationParser.h"
#include "AnimationObject.h"
#include "DataCollector.h"

bool AnimationLoader::loadData()
{
    AnimationLoader::loadDataByFileName("monkey_animation.xml");
    AnimationLoader::loadDataByFileName("cat_animation.xml");
    AnimationLoader::loadDataByFileName("skill_animation.xml");
    AnimationLoader::loadDataByFileName("effect_animation.xml");
    AnimationLoader::loadDataByFileName("tower_1_animation.xml");
    AnimationLoader::loadDataByFileName("tower_2_animation.xml");
    AnimationLoader::loadDataByFileName("creep_1_animation.xml");
    AnimationLoader::loadDataByFileName("pig_animation.xml");
        AnimationLoader::loadDataByFileName("bull_animation.xml");
    
    AnimationLoader::loadDataByFileName("coin1_animation.xml");
    AnimationLoader::loadDataByFileName("container_animation.xml");
    
    AnimationLoader::loadDataByFileName("effect_animation_1.xml");
    
    AnimationLoader::loadDataByFileName("maincrystal_animation.xml");
    
    return true;
}

bool AnimationLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    const char* characterName= docElement->Attribute(ATTRIBUTE_NAME);
    
    for (XMLElement* element = docElement->FirstChildElement(TAG_ANIMATION); element;
         element = element->NextSiblingElement())
    {
        CCString* animationName = CCString::create(element->Attribute(ATTRIBUTE_NAME));
        if (animationName)
        {
            AnimationObject* animationObject = XMLAnimationParser::getAnimationObjectFromXMLNode(element);
            std::string key = std::string(characterName) + std::string("-") + std::string(animationName->getCString());
            DataCollector::getInstance()->setAnimationObject(key.c_str(), animationObject);
        }
    }
    delete document;
    return true;
}
