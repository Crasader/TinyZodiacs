//
//  XMLProjectileDataParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#include "XMLProjectileDataParser.h"
#include "Constants.h"
#include "LayerIndexConstants.h"
#include "SoundManager.h"

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

ProjectileData XMLProjectileDataParser::loadXMLFile(const char *xmlFileName, std::string selectorId)
{
    ProjectileData data ;
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    //    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        //        CCLOG("Empty file: %s", fullPath.c_str());
        return data;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return data;
    }
    
    //Parse data
    XMLElement* docElement = document.FirstChildElement();
    if(docElement != NULL)
    {
        const XMLElement* result = XMLHelper::loadElementById(TAG_PROJECTILE, selectorId.c_str(), ATTRIBUTE_ID, docElement);
        if(result != NULL)
        {
            data.setProjectileBodyId(readProjectileBodyId(result->FirstChildElement(TAG_BODY)));
            data.setStateAnimation(readAnimationData(result->FirstChildElement(TAG_STATE_ANIMATION)));
            data.setGravityScale(readProjectileGravityScale(result->FirstChildElement(TAG_GRAVITY_SCALE)));
            data.setTerrainCollide(readTerrainCollide(result->FirstChildElement(TAG_COLLIDE_TERRAIN)));
            data.setPiercing(readPiercing(result->FirstChildElement(TAG_PIERCING)));
            data.setSoundData(readSoundData(result->FirstChildElement(TAG_SFX)));
        }
    }
    
    delete []pFileData;
    return data;
}

ProjectileData XMLProjectileDataParser::parseData(std::string projectileID)
{
    return loadXMLFile("list_projectile.xml", projectileID);
}

string XMLProjectileDataParser::readProjectileBodyId(const XMLElement* root)
{

    return XMLHelper::readString(root, "");
}

float XMLProjectileDataParser::readProjectileGravityScale(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

bool XMLProjectileDataParser::readTerrainCollide(const XMLElement* root)
{
    return XMLHelper::readBool(root, false);
}

int XMLProjectileDataParser::readPiercing(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

ProjectileStateAnimationData XMLProjectileDataParser::readAnimationData(const XMLElement* root)
{
    ProjectileStateAnimationData data;
    data.setAnimationLayerIndex(XMLHelper::readAttributeInt(root, ATTRIBUTE_ANIMATION_LAYER, ABOVE_CHARACTER_LAYER));
    data.setCreatedStateAnimationID(XMLHelper::readAttributeString(root, ATTRIBUTE_CREATE_STATE_ANIMATION, ""));
    data.setShootingStateAnimationID(XMLHelper::readAttributeString(root, ATTRIBUTE_SHOOTING_STATE_ANIMATION, ""));
    data.setDieStateAnimationID(XMLHelper::readAttributeString(root, ATTRIBUTE_DIE_STATE_ANIMATION, ""));
    data.setHitStateAnimationID(XMLHelper::readAttributeString(root, ATTRIBUTE_HIT_STATE_ANIMATION, ""));
//    CCLOG("");
    return data;
}

ProjectileSoundData XMLProjectileDataParser::readSoundData(const XMLElement* root)
{
    return SoundManager::loadProjectileSoundData(XMLHelper::readString(root, "").c_str());
}





