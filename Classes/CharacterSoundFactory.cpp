//
//  CharacterSoundFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/4/14.
//
//

#include "CharacterSoundFactory.h"

#define TAG_CHARACTER_SOUND "character_sound"
#define ATTRIBUTE_ID "id"

CharacterSoundData CharacterSoundFactory::loadCharacterSoundDataFromXMLFile(const char* soundId, const char* xmlFileName)
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_CHARACTER_SOUND, soundId, ATTRIBUTE_ID, docElement);
    if(result != NULL)
    {
        data = XMLCharacterSoundParser::loadData(result);
    }
    
    delete []pFileData;
    return data;
}

CharacterSoundData CharacterSoundFactory::loadCharacterSoundData(const char* soundId)
{
    return CharacterSoundFactory::loadCharacterSoundDataFromXMLFile(soundId, "character_sounds.xml");
}