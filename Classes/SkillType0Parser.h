//
//  SkillType0Parser.h
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#ifndef __TinyZodiacs__SkillType0Parser__
#define __TinyZodiacs__SkillType0Parser__

#include <iostream>
#include "cocos2d.h"
#include "NormalMeleeSkillData.h"
#include "Box2D/Box2D.h"
#include "PhysicConstants.h"
#include "GB2ShapeCache-x.h"



#define TAG_JOINT "joints"
#define TAG_HOLDER "holder"
#define TAG_THIS "this"

#define ATTRIBUTE_X "x"
#define ATTRIBUTE_Y "y"
#define ATTRIBUTE_OFFSET_X "offsetX"
#define ATTRIBUTE_OFFSET_Y "offsetY"

#define TAG_JOINTS "joints"
#define TAG_HOLDER "holder"
#define TAG_THIS "this"

#define TAG_BODY "body"
#define TAG_DAMAGE "damage"
#define TAG_COOL_DOWN "cool_down"
#define TAG_DELAY "delay"
#define TAG_LIFE_TIME "life_time"
#define TAG_ANIMATION "animation"


using namespace tinyxml2;

USING_NS_CC;
class SkillType0Parser
{
private:
protected:
    static int readDamage(const XMLElement* root);
    static float readCoolDown(const XMLElement* root);
    static JointDef readJoinDef(const XMLElement* root);
    static void readJointDef(const NormalMeleeSkillData* data);
    static b2Body* readBody(const XMLElement* root, b2World* world);
    static float readDelay(const XMLElement* root);
    static float readLifeTime(const XMLElement* root);
    static AnimationObject* readAnimation(const XMLElement* root);

public:
    static NormalMeleeSkillData parse(const XMLElement* root, b2World* world);
};
#endif /* defined(__TinyZodiacs__SkillType0Parser__) */
