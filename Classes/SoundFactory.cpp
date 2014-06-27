//
//  SoundFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#include "SoundFactory.h"

#define TAG_CHARACTER_SOUND "character_sound"
#define ATTRIBUTE_CHARACTER_SOUND_ID "id"

#define TAG_PROJECTILE_SOUND "projectile_sound"
#define ATTRIBUTE_PROJECTILE_SOUND_ID "id"

#define TAG_SKILL_SOUND "skill_sound"
#define ATTRIBUTE_SKILL_SOUND_ID "id"


CharacterSoundData SoundFactory::loadCharacterSoundDataFromXMLFile(const char* soundId, const char* xmlFileName)
{
    
    CharacterSoundData data;
    
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_CHARACTER_SOUND, soundId, ATTRIBUTE_CHARACTER_SOUND_ID, docElement);
    if(result != NULL)
    {
        data = XMLCharacterSoundParser::loadData(result);
    }
    
    delete []pFileData;
    return data;
}

CharacterSoundData SoundFactory::loadCharacterSoundData(const char* soundId)
{
    return SoundFactory::loadCharacterSoundDataFromXMLFile(soundId, "character_sounds.xml");
}

/****************/

ProjectileSoundData SoundFactory::loadProjectileSoundDataFromXMLFile(const char* soundId, const char* xmlFileName)
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_PROJECTILE_SOUND, soundId, ATTRIBUTE_PROJECTILE_SOUND_ID, docElement);
    if(result != NULL)
    {
        data = XMLProjectileSoundParser::loadData(result);
    }
    
    delete []pFileData;
    return data;
}

ProjectileSoundData SoundFactory::loadProjectileSoundData(const char* soundId)
{
    return SoundFactory::loadProjectileSoundDataFromXMLFile(soundId, "projectile_sounds.xml");
}

/*************************/

SkillSoundData SoundFactory::loadSkillSoundDataFromXMLFile(const char* soundId, const char* xmlFileName)
{
    
    SkillSoundData data;
    
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_SKILL_SOUND, soundId, ATTRIBUTE_SKILL_SOUND_ID, docElement);
    if(result != NULL)
    {
        data = XMLSkillSoundParser::loadData(result);
    }
    
    delete []pFileData;
    return data;
}

SkillSoundData SoundFactory::loadSkillSoundData(const char* soundId)
{
    return SoundFactory::loadSkillSoundDataFromXMLFile(soundId, "skill_sounds.xml");
}