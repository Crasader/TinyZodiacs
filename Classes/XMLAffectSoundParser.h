//
//  XMLAffectSoundParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#ifndef __TinyZodiacs__XMLAffectSoundParser__
#define __TinyZodiacs__XMLAffectSoundParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "SkillSoundData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLAffectSoundParser
{
private:
protected:
    static std::string readSoundString(const XMLElement* root);
public:
    static std::string loadData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLAffectSoundParser__) */
