//
//  SkillFactory.h
//  TinyZodiacs
//
//  Created by Nhut on 3/25/14.
//
//

#ifndef __TinyZodiacs__SkillFactory__
#define __TinyZodiacs__SkillFactory__

#include <iostream>
#include "cocos2d.h"
#include "Box2d/Box2D.h"
#include "AbstractSkill.h"
#include "GB2ShapeCache-x.h"
#include "PhysicConstants.h"
#include "GameObject.h"
#include "SkillDTO.h"

#define ATTRIBUTE_ID "id";
#define ATTRIBUTE_TYPE "type";

#define ATTRIBUTE_X "x";
#define ATTRIBUTE_Y "y";
#define ATTRIBUTE_OFFSET "offset";

#define TAG_SKILL "skill";
#define TAG_BODY "body";
#define TAG_DAMAGE "damage";
#define TAG_COOL_DOWN "cool_down";
#define TAG_META_DATA "meta_data";

#define TAG_JOINT "joint";
#define TAG_HOLDER "holder";
#define TAG_THIS "this";

using namespace tinyxml2;

class SkillFactory
{
private:
protected:
    static SkillDTO loadXMLFile(string id,const char* xmlFileName);
    static const XMLElement* loadElementById(string id, const XMLElement* root);
public:
    static AbstractSkill* createSkill(string id, b2World* world, GameObject* holder);
};

#endif /* defined(__TinyZodiacs__SkillFactory__) */
