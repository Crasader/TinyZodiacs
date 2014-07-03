//
//  SkillAnimationDataFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 7/1/14.
//
//

#include "SkillAnimationDataFactory.h"

#define TAG_SKILL_ANIMATION "skill_animation"
#define ATTRIBUTE_ID "id"

SkillAnimationData SkillAnimationDataFactory::loadSkillAnimationDataFromXMLFile(const char* animationId, const char* xmlFileName)
{
    SkillAnimationData data;
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    //    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        //        CCLOG("Empty file: %s", fullPath.c_str());
        return data;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return data;
    }
    
    //Parse data
    XMLElement* docElement = document.FirstChildElement();
    const XMLElement* result = XMLHelper::loadElementById(TAG_SKILL_ANIMATION, animationId, ATTRIBUTE_ID, docElement);
    if(result != NULL)
    {
        data = XMLSkillAnimationParser::loadData(result);
    }
    
    delete []pFileData;
    return data;

}

SkillAnimationData SkillAnimationDataFactory::loadSkillAnimationData(const char* animationId)
{
    return loadSkillAnimationDataFromXMLFile(animationId, "list_skill_animation.xml");
}