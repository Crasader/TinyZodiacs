//
//  XMLProjectileSoundParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/24/14.
//
//

#ifndef __TinyZodiacs__XMLProjectileSoundParser__
#define __TinyZodiacs__XMLProjectileSoundParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "ProjectileSoundData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLProjectileSoundParser
{
private:
protected:
    static std::string readCreateSoundString(const XMLElement* root);
    static std::string readShootSoundString(const XMLElement* root);
    static std::string readHitSoundString(const XMLElement* root);
    static std::string readDieSoundString(const XMLElement* root);
    
public:
    static ProjectileSoundData loadData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLProjectileSoundParser__) */
