//
//  XMLProjectileDataParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#ifndef __TinyZodiacs__XMLProjectileDataParser__
#define __TinyZodiacs__XMLProjectileDataParser__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "XMLHelper.h"
#include "ProjectileData.h"
#include "ProjectileSoundData.h"

using namespace tinyxml2;

class XMLProjectileDataParser
{
private:
protected:
    static std::string readProjectileBodyId(const XMLElement* root);
    static float readProjectileGravityScale(const XMLElement* root);
    static bool readTerrainCollide(const XMLElement* root);
    static int readPiercing(const XMLElement* root);
    static ProjectileStateAnimationData readAnimationData(const XMLElement* root);
    static ProjectileSoundData readSoundData(const XMLElement* root);
    
    static ProjectileData loadXMLFile(const char *xmlFileName, std::string selectorId);
public:
    static ProjectileData parseData(std::string projectileID);
};

#endif /* defined(__TinyZodiacs__XMLProjectileDataParser__) */
