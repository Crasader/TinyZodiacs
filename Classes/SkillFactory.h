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
#include "Constants.h"

#define SKILL_XML_FILE "list_skill.xml"

#define ATTRIBUTE_ID "id"
#define ATTRIBUTE_TYPE "type"

#define TAG_SKILL "skill"
#define TAG_TEXTURE "texture"
#define TAG_SELECTED "selected"
#define TAG_ACTIVE "active"
#define TAG_DEACTIVE "deactive"



using namespace tinyxml2;

class SkillFactory
{
private:
protected:
    static AbstractSkill* loadXMLFile(const char* id,const char* xmlFileName, b2World* world, GameObject* holder, bool isLocal, ButtonID buttonIndex);
    static const XMLElement* loadElementById(const char* id, const XMLElement* root);
    
    static string readSkillType(const XMLElement* root);
    static std::string readTextureId(const XMLElement* root, string tagName);
    
    static void setButton();

public:
    static AbstractSkill* createSkill(const char* id, b2World* world, GameObject* holder, bool isLocal, ButtonID buttonIndex);
};

#endif /* defined(__TinyZodiacs__SkillFactory__) */
