//
//  CharacterSoundFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/4/14.
//
//

#ifndef __TinyZodiacs__CharacterSoundFactory__
#define __TinyZodiacs__CharacterSoundFactory__

#include <iostream>
#include "CharacterSoundData.h"
#include "cocos2d.h"
#include "XMLCharacterSoundParser.h"

USING_NS_CC;
using namespace tinyxml2;

class CharacterSoundFactory
{
private:
    static CharacterSoundData loadCharacterSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
protected:
public:
    static CharacterSoundData loadCharacterSoundData(const char* soundId);
};
#endif /* defined(__TinyZodiacs__CharacterSoundFactory__) */
