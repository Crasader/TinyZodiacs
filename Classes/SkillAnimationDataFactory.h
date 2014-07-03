//
//  SkillAnimationDataFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 7/1/14.
//
//

#ifndef __TinyZodiacs__SkillAnimationDataFactory__
#define __TinyZodiacs__SkillAnimationDataFactory__

#include <iostream>
#include "cocos2d.h"
#include "XMLSkillAnimationParser.h"

USING_NS_CC;
using namespace tinyxml2;

class SkillAnimationDataFactory
{
private:
    static SkillAnimationData loadSkillAnimationDataFromXMLFile(const char* animationId, const char* xmlFileName);
protected:
public:
    static SkillAnimationData loadSkillAnimationData(const char* animationId);
};
#endif /* defined(__TinyZodiacs__SkillAnimationDataFactory__) */
