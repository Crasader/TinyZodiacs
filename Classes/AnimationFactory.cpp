//
//  AnimationFactory.cpp
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#include "AnimationFactory.h"
#include "XMLAnimationParser.h"
#include "AnimationObject.h"

using namespace tinyxml2;
USING_NS_CC;
static AnimationFactory* sharedFactory = NULL;

AnimationFactory::AnimationFactory()
{
    this->animationDictionary = CCDictionary::create();
    this->animationDictionary->retain();
}

AnimationFactory::~AnimationFactory()
{
    CC_SAFE_RELEASE(this->animationDictionary);
}

AnimationFactory* AnimationFactory::getSharedFactory()
{
    if (!sharedFactory)
    {
        sharedFactory = new AnimationFactory();
        //  this->sharedFactory->init();
    }
    return sharedFactory;
}

bool AnimationFactory::loadXMLAnimation()
{
    loadXMLAnimationByNameFile("monkey_animation.xml");
    loadXMLAnimationByNameFile("skill_animation.xml");
    
    return true;
}

bool AnimationFactory::loadXMLAnimationByNameFile(const char *xmlFileName)
{
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        CCLOG("Empty file: %s", fullPath.c_str());
        return false;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return false;
    }
    
    // Get plist file
    
    
    XMLElement* docElement = document.FirstChildElement();
    
    const char* characterName= docElement->Attribute("name");
    const char* plistFileName = docElement->Attribute("plist_name");
    const char* imageFileName = docElement->Attribute("image_name");
    
    std::string plistFileNamFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFileName);
    std::string imageFileNameFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(imageFileName);
    
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFileNamFullPath.c_str());
    
    for (XMLElement* element = docElement->FirstChildElement("animation"); element; element = element->NextSiblingElement())
    {
        CCString* animationName = CCString::create(element->Attribute("name"));
        if (animationName) {
            
            AnimationObject* animation = XMLAnimationParser::getAnimationObjectFromXMLNode(element);
            std::string keyName = std::string(characterName) + std::string("-") + std::string(animationName->getCString());
            this->animationDictionary->setObject(animation, keyName);
        }
    }
    
    delete []pFileData;
    return true;
    
}
CCAnimation* AnimationFactory::getAnimationByName(const char *keyAnimation)
{
    return (CCAnimation*)this->animationDictionary->objectForKey(keyAnimation);
}

AnimationObject* AnimationFactory::getAnimationObjectByName(const char *keyAnimation)
{
    return (AnimationObject*)this->animationDictionary->objectForKey(keyAnimation);
}