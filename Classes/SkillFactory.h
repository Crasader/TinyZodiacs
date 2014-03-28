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
#include "Constants.h"
#include "SkillType0Parser.h"
#include "NormalAttack.h"

#define ATTRIBUTE_ID "id"
#define ATTRIBUTE_TYPE "type"

#define TAG_SKILL "skill"

using namespace tinyxml2;

class SkillFactory
{
private:
protected:
    static AbstractSkill* loadXMLFile(const char* id,const char* xmlFileName, b2World* world, GameObject* holder);
    static const XMLElement* loadElementById(const char* id, const XMLElement* root);
    
    static int readSkillType(const XMLElement* root);

public:
    static AbstractSkill* createSkill(const char* id, b2World* world, GameObject* holder);
};

#endif /* defined(__TinyZodiacs__SkillFactory__) */
