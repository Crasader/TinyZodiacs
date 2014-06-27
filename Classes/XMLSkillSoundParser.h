//
//  XMLSkillSoundParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#ifndef __TinyZodiacs__XMLSkillSoundParser__
#define __TinyZodiacs__XMLSkillSoundParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "SkillSoundData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLSkillSoundParser
{
private:
protected:
    static std::string readExcuteSoundString(const XMLElement* root);
    static std::string readHitSoundString(const XMLElement* root);
    static std::string readStopSoundString(const XMLElement* root);    
public:
    static SkillSoundData loadData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLSkillSoundParser__) */
