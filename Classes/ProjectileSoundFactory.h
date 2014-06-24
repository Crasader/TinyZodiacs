//
//  ProjectileSoundFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/24/14.
//
//

#ifndef __TinyZodiacs__ProjectileSoundFactory__
#define __TinyZodiacs__ProjectileSoundFactory__

#include <iostream>
#include "ProjectileSoundData.h"
#include "cocos2d.h"
#include "XMLProjectileSoundParser.h"

USING_NS_CC;
using namespace tinyxml2;

class ProjectileSoundFactory
{
private:
    static ProjectileSoundData loadProjectileSoundDataFromXMLFile(const char* soundId, const char* xmlFileName);
protected:
public:
    static ProjectileSoundData loadProjectileSoundData(const char* soundId);
};
#endif /* defined(__TinyZodiacs__ProjectileSoundFactory__) */
