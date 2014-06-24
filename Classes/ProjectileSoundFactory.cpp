//
//  ProjectileSoundFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/24/14.
//
//

#include "ProjectileSoundFactory.h"
#define TAG_PROJECTILE_SOUND "projectile_sound"
#define ATTRIBUTE_ID "id"

ProjectileSoundData ProjectileSoundFactory::loadProjectileSoundDataFromXMLFile(const char* soundId, const char* xmlFileName)
{
    
    ProjectileSoundData data;
    
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_PROJECTILE_SOUND, soundId, ATTRIBUTE_ID, docElement);
    if(result != NULL)
    {
        data = XMLProjectileSoundParser::loadData(result);
    }
    
    delete []pFileData;
    return data;
}

ProjectileSoundData ProjectileSoundFactory::loadProjectileSoundData(const char* soundId)
{
    return ProjectileSoundFactory::loadProjectileSoundDataFromXMLFile(soundId, "projectile_sounds.xml");
}