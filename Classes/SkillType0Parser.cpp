//
//  SkillType0Parser.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#include "SkillType0Parser.h"

int SkillType0Parser::readDamage(const XMLElement* root)
{
    if(root != NULL)
    {
        string damageValue = root->GetText();
        int value = atoi(damageValue.c_str());
        return value;
    }
    return 0;
}

float SkillType0Parser::readCoolDown(const XMLElement* root)
{
    if(root != NULL)
    {
        string coolDownValue = root->GetText();
        float value = atoi(coolDownValue.c_str());
        return value;
    }
    return 0;
}

JointDef SkillType0Parser::readJoinDef(const XMLElement* root)
{
    JointDef def;
    if(root != NULL)
    {
        string xString = root->Attribute(ATTRIBUTE_X);
        int x = atoi(xString.c_str());
        
        string yString = root->Attribute(ATTRIBUTE_Y);
        int y = atoi(yString.c_str());
        
        string xOffsetString = root->Attribute(ATTRIBUTE_OFFSET_X);
        int xOffset = atoi(xOffsetString.c_str());
        
        string yOffsetString = root->Attribute(ATTRIBUTE_OFFSET_Y);
        int yOffset = atoi(yOffsetString.c_str());
        
        def.x=x;
        def.y=y;
        def.offsetX=xOffset;
        def.offsetY=yOffset;
    }
    return def;
}


b2Body* SkillType0Parser::readBody(const XMLElement* root, b2World* world)
{
    if(root != NULL)
    {
        string bodyId = root->GetText();
        
        //Create body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.angle = ccpToAngle(ccp(0,0));
        bodyDef.fixedRotation=true;
        bodyDef.bullet = true;
        
        b2Body *body = world->CreateBody(&bodyDef);
        
        gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
        sc->addFixturesToBody(body, bodyId);
        
        return body;
    }
    return NULL;
    //Create body
}

float SkillType0Parser::readDelay(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = root->GetText();
        float value = atof(typeValue.c_str());
        return value;
    }
    return 0;
}

NormalMeleeSkillData SkillType0Parser::parse(const XMLElement* root, b2World* world)
{
    NormalMeleeSkillData data;
    data.setDamage(readDamage(root->FirstChildElement(TAG_DAMAGE)));
    data.setCoolDown(readDamage(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setskillSensor(readBody(root->FirstChildElement(TAG_BODY), world));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));

    return data;
}