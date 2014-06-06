//
//  XMLCharacterSoundParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/4/14.
//
//

#ifndef __TinyZodiacs__XMLCharacterSoundParser__
#define __TinyZodiacs__XMLCharacterSoundParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "CharacterSoundData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLCharacterSoundParser
{
private:
protected:
    static std::string readHurtSoundString(const XMLElement* root);
    static std::string readDeathSoundString(const XMLElement* root);
    static std::string readJumpSoundString(const XMLElement* root);

public:
    static CharacterSoundData loadData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLCharacterSoundParser__) */
