//
//  XMLItemSoundParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#ifndef __TinyZodiacs__XMLItemSoundParser__
#define __TinyZodiacs__XMLItemSoundParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "ItemSoundData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLItemSoundParser
{
private:
protected:
    static std::string readAppearSoundString(const XMLElement* root);
    static std::string readDisappearSoundString(const XMLElement* root);
    static std::string readDestroySoundString(const XMLElement* root);
    static std::string readConsumeSoundString(const XMLElement* root);
public:
    static ItemSoundData loadData(const XMLElement* root);
};


#endif /* defined(__TinyZodiacs__XMLItemSoundParser__) */
