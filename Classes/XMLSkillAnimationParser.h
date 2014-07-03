//
//  XMLSkillAnimationParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 7/1/14.
//
//

#ifndef __TinyZodiacs__XMLSkillAnimationParser__
#define __TinyZodiacs__XMLSkillAnimationParser__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "SkillAnimationData.h"

USING_NS_CC;
using namespace tinyxml2;

class XMLSkillAnimationParser
{
private:
protected:
    static AnimationObject* readPreExcuteAnimation(const XMLElement* root);
    static AnimationObject* readExcuteAnimation(const XMLElement* root);
    static AnimationObject* readPreStopAnimation(const XMLElement* root);
    static AnimationObject* readStopAnimation(const XMLElement* root);
public:
    static SkillAnimationData loadData(const XMLElement* root);
};
#endif /* defined(__TinyZodiacs__XMLSkillAnimationParser__) */
