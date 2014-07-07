//
//  EffectFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/17/14.
//
//

#include "EffectFactory.h"

#include "XMLHelper.h"
#include "LayerIndexConstants.h"
#include "SoundManager.h"

using namespace tinyxml2;

EffectData* EffectFactory::createEffectData(const char* key)
{
    EffectData* effect = loadXMLFile(key, EFFECT_XML_FILE);
    return effect;
}

EffectData* EffectFactory::loadXMLFile(const char* key, const char *xmlFileName)
{

    EffectData* data = NULL ;
    
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
    const XMLElement* result = XMLHelper::loadElementById(TAG_EFFECT, key, ATTRIBUTE_ID, docElement);
    if(result != NULL)
    {
        data = new EffectData();
        data->setAnimationId(readAnimationId(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setAnimationLayerIndex(readAnimationLayerIndex(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setMinRotateAngle(readMinRotation(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setMaxRotateAngle(readMaxRotation(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setMinScale(readMinScale(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setMaxScale(readMaxScale(result->FirstChildElement(TAG_ANIMATION_ID)));
        data->setRepeatTimes(readRepeatTimes(result->FirstChildElement(TAG_ANIMATION_ID)));
        
        if(result->FirstChildElement(TAG_JOINTS) != NULL)
        {
            data->setJointDefA(readJoinDef(result->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
            data->setJointDefB(readJoinDef(result->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
        }

        data->setChance(readChance(result->FirstChildElement(TAG_CHANCE)));
        data->setCritChance(readCritChance(result->FirstChildElement(TAG_CRIT_CHANCE)));
        data->setCritRatio(readCritRatio(result->FirstChildElement(TAG_CRIT_RATIO)));

        data->setHealth(readHealth(result->FirstChildElement(TAG_HP)));
        data->setAttack(readAttack(result->FirstChildElement(TAG_ATK)));
        data->setAttackSpeed(readAttackSpeed(result->FirstChildElement(TAG_ATK_SPEED)));
        data->setSpeed(readSpeed(result->FirstChildElement(TAG_SPEED)));
        data->setJumpHeight(readJumpHeight(result->FirstChildElement(TAG_JUMP_HEIGHT)));
        data->setMaxJump(readMaxJump(result->FirstChildElement(TAG_MAX_JUMP)));
        data->setDefense(readDefense(result->FirstChildElement(TAG_DEF)));

        data->setLifeTime(readLifeTime(result->FirstChildElement(TAG_LIFE_TIME)));
        data->settimeTick(readTimeTick(result->FirstChildElement(TAG_TIME_TICK)));
        
        data->setSoundEffect(readSFX(result->FirstChildElement(TAG_SFX)));
        data->setApplyType(readApplyType(result->FirstChildElement(TAG_APPLY_TYPE)));
    }
    
    delete []pFileData;
    return data;
}

std::string EffectFactory::readAnimationId(const XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

int EffectFactory::readAnimationLayerIndex(const XMLElement* root)
{
    return XMLHelper::readAttributeInt(root, ATTRIBUTE_ANIMATION_LAYER, ABOVE_CHARACTER_LAYER);
}

float EffectFactory::readMinRotation(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MIN_ROTATE_ANGLE, 0);
}

float EffectFactory::readMaxRotation(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MAX_ROTATE_ANGLE, 0);
}

float EffectFactory::readMinScale(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MIN_SCALE, 1);
}

float EffectFactory::readMaxScale(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MAX_SCALE, 1);
}

int EffectFactory::readRepeatTimes(const XMLElement* root)
{
    return XMLHelper::readAttributeInt(root, ATTRIBUTE_REPEAT_TIMES, 1);
}

float EffectFactory::readChance(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

float EffectFactory::readCritChance(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

float EffectFactory::readCritRatio(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 1);
}

int EffectFactory::readHealth(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int EffectFactory::readAttack(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}
int EffectFactory::readSpeed(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int EffectFactory::readAttackSpeed(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int EffectFactory::readMaxJump(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int EffectFactory::readJumpHeight(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int EffectFactory::readDefense(const XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

float EffectFactory::readLifeTime(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

float EffectFactory::readTimeTick(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

JointDef EffectFactory::readJoinDef(const XMLElement* root)
{
    JointDef def;
    if(root != NULL)
    {
        //        string xString = root->Attribute(ATTRIBUTE_X);
        //        int x = atoi(xString.c_str());
        //
        //        string yString = root->Attribute(ATTRIBUTE_Y);
        //        int y = atoi(yString.c_str());
        //
        //        string xOffsetString = root->Attribute(ATTRIBUTE_OFFSET_X);
        //        float xOffset = atof(xOffsetString.c_str());
        //
        //        string yOffsetString = root->Attribute(ATTRIBUTE_OFFSET_Y);
        //        float yOffset = atof(yOffsetString.c_str());
        def.x=XMLHelper::readAttributeInt(root, ATTRIBUTE_X, 0);
        def.y=XMLHelper::readAttributeInt(root, ATTRIBUTE_Y, 0);
        def.offsetX=XMLHelper::readAttributeFloat(root, ATTRIBUTE_OFFSET_X, 0);
        def.offsetY=XMLHelper::readAttributeFloat(root, ATTRIBUTE_OFFSET_Y, 0);
    }
    return def;
}

std::string EffectFactory::readSFX(const XMLElement* root)
{
    std::string soundId = XMLHelper::readString(root, "");
    return SoundManager::loadAffectSoundData(soundId.c_str());
}

ApplyType EffectFactory::readApplyType(const XMLElement* root)
{
    ApplyType type = (ApplyType)XMLHelper::readInt(root, APPLY_ONCE);
    return type;
}