//
//  XMLAnimationDataParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 5/31/14.
//
//

#include "XMLAnimationDataParser.h"
#include "LayerIndexConstants.h"

#define ATTRIBUTE_ANIMATION_LAYER "animation_layer"
#define ATTRIBUTE_MIN_ROTATE_ANGLE "minRotateAngle"
#define ATTRIBUTE_MAX_ROTATE_ANGLE "maxRotateAngle"
#define ATTRIBUTE_MIN_SCALE "minScale"
#define ATTRIBUTE_MAX_SCALE "maxScale"
#define ATTRIBUTE_REPEAT_TIMES "repeatTimes"

std::string XMLAnimationDataParser::readAnimationId(const XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

int XMLAnimationDataParser::readAnimationLayerIndex(const XMLElement* root)
{
    return XMLHelper::readAttributeInt(root, ATTRIBUTE_ANIMATION_LAYER, ABOVE_CHARACTER_LAYER);
}

float XMLAnimationDataParser::readMinRotation(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MIN_ROTATE_ANGLE, 0);
}

float XMLAnimationDataParser::readMaxRotation(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MAX_ROTATE_ANGLE, 0);
}

float XMLAnimationDataParser::readMinScale(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MIN_SCALE, 1);
}

float XMLAnimationDataParser::readMaxScale(const XMLElement* root)
{
    return XMLHelper::readAttributeFloat(root, ATTRIBUTE_MAX_SCALE, 1);
}

int XMLAnimationDataParser::readRepeatTimes(const XMLElement* root)
{
    return XMLHelper::readAttributeInt(root, ATTRIBUTE_REPEAT_TIMES, 1);
}

AnimationData XMLAnimationDataParser::parseData(const XMLElement* root)
{
    AnimationData data;
    if(root != NULL)
    {
        data.setAnimationId(readAnimationId(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setAnimationLayerIndex(readAnimationLayerIndex(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setMinRotateAngle(readMinRotation(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setMaxRotateAngle(readMaxRotation(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setMinScale(readMinScale(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setMaxScale(readMaxScale(root->FirstChildElement(TAG_ANIMATION_ID)));
        data.setRepeatTimes(readRepeatTimes(root->FirstChildElement(TAG_ANIMATION_ID)));
    }
    return data;
}
