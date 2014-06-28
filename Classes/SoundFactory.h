//
//  SoundFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#ifndef __TinyZodiacs__SoundFactory__
#define __TinyZodiacs__SoundFactory__

#include <iostream>
#include "cocos2d.h"

#include "CharacterSoundData.h"
#include "XMLCharacterSoundParser.h"

#include "ProjectileSoundData.h"
#include "XMLProjectileSoundParser.h"

#include "SkillSoundData.h"
#include "XMLSkillSoundParser.h"

#include "XMLAffectSoundParser.h"

#include "ItemSoundData.h"
#include "XMLItemSoundParser.h"

USING_NS_CC;
using namespace tinyxml2;

class SoundFactory
{
private:
    static CharacterSoundData loadCharacterSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static ProjectileSoundData loadProjectileSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static SkillSoundData loadSkillSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static std::string loadAffectSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static ItemSoundData loadItemSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
protected:
public:
    static CharacterSoundData loadCharacterSoundData(const char* soundId);
    static ProjectileSoundData loadProjectileSoundData(const char* soundId);
    static SkillSoundData loadSkillSoundData(const char* soundId);
    static std::string loadAffectSoundData(const char* soundId);
    static ItemSoundData loadItemSoundData(const char* soundId);
};
#endif /* defined(__TinyZodiacs__SoundFactory__) */
