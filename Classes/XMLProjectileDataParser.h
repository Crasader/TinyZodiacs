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

#define TAG_PROJECTILE "projectile"
#define TAG_GRAVITY_SCALE "gravity_scale"
#define TAG_COLLIDE_TERRAIN "collide_terrain"
#define TAG_PIERCING "piercing"
#define TAG_BODY "body"
#define TAG_STATE_ANIMATION "state_animation"
#define TAG_SFX "sfx"
#define ATTRIBUTE_ANIMATION_LAYER "animation_layer"
#define ATTRIBUTE_CREATE_STATE_ANIMATION "created_state_animation"
#define ATTRIBUTE_SHOOTING_STATE_ANIMATION "shooting_state_animation"
#define ATTRIBUTE_HIT_STATE_ANIMATION "hit_state_ainmation"
#define ATTRIBUTE_DIE_STATE_ANIMATION "die_state_animation"
#define ATTRIBUTE_ID "id"



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
