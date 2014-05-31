//
//  EffectFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/17/14.
//
//

#ifndef __TinyZodiacs__EffectFactory__
#define __TinyZodiacs__EffectFactory__

#include <iostream>
#include "cocos2d.h"
#include "XMLHelper.h"
#include "EffectData.h"
#include "AnimationObject.h"
#include "PhysicConstants.h"


USING_NS_CC;
using namespace tinyxml2;

#define EFFECT_XML_FILE "list_effect.xml"
#define TAG_EFFECT "effect"

//#define TAG_ANIMATION_LAYER "animation_layer"
#define TAG_JOINTS "joints"
#define TAG_HOLDER "holder"
#define TAG_THIS "this"

#define TAG_CHANCE "chance"
#define TAG_CRIT_CHANCE "crit_chance"
#define TAG_CRIT_RATIO "crit"

#define TAG_HP "hp"
#define TAG_ATK "atk"
#define TAG_DEF "def"
#define TAG_SPEED "speed"
#define TAG_ATK_SPEED "atk_speed"
#define TAG_MAX_JUMP "max_jump"
#define TAG_JUMP_HEIGHT "jump_height"

#define TAG_LIFE_TIME "life_time"
#define TAG_TIME_TICK "time_tick"

#define ATTRIBUTE_ID "id"
#define ATTRIBUTE_X "x"
#define ATTRIBUTE_Y "y"
#define ATTRIBUTE_OFFSET_X "offsetX"
#define ATTRIBUTE_OFFSET_Y "offsetY"

//#define TAG_ANIMATION_ID "animation"
//
//#define ATTRIBUTE_ANIMATION_LAYER "animation_layer"
//#define ATTRIBUTE_MIN_ROTATE_ANGLE "minRotateAngle"
//#define ATTRIBUTE_MAX_ROTATE_ANGLE "maxRotateAngle"
//#define ATTRIBUTE_MIN_SCALE "minScale"
//#define ATTRIBUTE_MAX_SCALE "maxScale"
//#define ATTRIBUTE_REPEAT_TIMES "repeatTimes"


class EffectFactory
{
private:
protected:
    static std::string readAnimationId(const XMLElement* root);
    static int readAnimationLayerIndex(const XMLElement* root);
    static JointDef readJoinDef(const XMLElement* root);
    static float readMinRotation(const XMLElement* root);
    static float readMaxRotation(const XMLElement* root);
    static float readMinScale(const XMLElement* root);
    static float readMaxScale(const XMLElement* root);
    static int readRepeatTimes(const XMLElement* root);

    
    static float readChance(const XMLElement* root);
    static float readCritChance(const XMLElement* root);
    static float readCritRatio(const XMLElement* root);
    
    static int readHealth(const XMLElement* root);
    static int readAttack(const XMLElement* root);
    static int readSpeed(const XMLElement* root);
    static int readAttackSpeed(const XMLElement* root);
    static int readMaxJump(const XMLElement* root);
    static int readJumpHeight(const XMLElement* root);
    static int readDefense(const XMLElement* root);

    static float readLifeTime(const XMLElement* root);
    static float readTimeTick(const XMLElement* root);
public:
    static EffectData* loadXMLFile(const char* key, const char* xmlFileName);
    static EffectData* createEffectData(const char* key);
};
#endif /* defined(__TinyZodiacs__EffectFactory__) */
