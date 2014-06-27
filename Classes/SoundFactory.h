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

USING_NS_CC;
using namespace tinyxml2;

class SoundFactory
{
private:
    static CharacterSoundData loadCharacterSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static ProjectileSoundData loadProjectileSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
    static SkillSoundData loadSkillSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
protected:
public:
    static CharacterSoundData loadCharacterSoundData(const char* soundId);
    static ProjectileSoundData loadProjectileSoundData(const char* soundId);
    static SkillSoundData loadSkillSoundData(const char* soundId);
};
#endif /* defined(__TinyZodiacs__SoundFactory__) */
