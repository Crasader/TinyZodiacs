//
//  SkillType0Parser.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#include "SkillType0Parser.h"
#include "LayerIndexConstants.h"
#include "EffectData.h"
#include "EffectFactory.h"
#include "DataCollector.h"

//int SkillType0Parser::readDamage(const XMLElement* root)
//{
//    if(root != NULL)
//    {
//        string damageValue = root->GetText();
//        int value = atoi(damageValue.c_str());
//        return value;
//    }
//    return 0;
//}

float SkillType0Parser::readCoolDown(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string coolDownValue = root->GetText();
//        float value = atof(coolDownValue.c_str());
//        return value;
//    }
//    return 0;
    return XMLHelper::readFloat(root, -1);
}

float SkillType0Parser::readLifeTime(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string coolDownValue = root->GetText();
//        float value = atof(coolDownValue.c_str());
//        return value;
//    }
//    return -1;
    return XMLHelper::readFloat(root, -1);
}

JointDef SkillType0Parser::readJoinDef(const XMLElement* root)
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


b2Body* SkillType0Parser::readBody(const XMLElement* root, b2World* world)
{
    if(root != NULL)
    {
        std::string bodyId = XMLHelper::readString(root, "");
        
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
//    if(root != NULL)
//    {
//        string typeValue = root->GetText();
//        float value = atof(typeValue.c_str());
//        return value;
//    }
//    return 0;
    return XMLHelper::readFloat(root, 0);
}

//float SkillType0Parser::readCriticalChance(const XMLElement* root)
//{
//    if(root != NULL)
//    {
//        string typeValue = root->GetText();
//        float value = atof(typeValue.c_str());
//        return value;
//    }
//    return 0;
//}

AnimationObject* SkillType0Parser::readAnimation(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return NULL;
        }
        AnimationObject* anim = DataCollector::getInstance()->getAnimationObjectByKey(typeValue.c_str());
        return anim;
    }
    return NULL;

}

int SkillType0Parser::readAnimationLayerIndex(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string layerValue = root->GetText();
//        int value = atoi(layerValue.c_str());
//        return value;
//    }
//    return ABOVE_CHARACTER_LAYER;
    return XMLHelper::readInt(root, ABOVE_CHARACTER_LAYER);
}

SkillTarget SkillType0Parser::readTarget(const XMLElement* root)
{
//    if(root != NULL)
//    {
//        string layerValue = root->GetText();
//        int value = atoi(layerValue.c_str());
        int value = XMLHelper::readInt(root, ENEMY);
        return static_cast<SkillTarget>(value);
//    }
//    return ENEMY;
}

vector<EffectData> SkillType0Parser::readEffectList(const XMLElement* root)
{
    vector<EffectData> effectList;
    if(root != NULL)
    {
        const XMLElement* effectNode = root->FirstChildElement(TAG_EFFECT);
        if(effectNode == NULL)
        {
            return effectList;
        }
        while (effectNode != NULL)
        {
            std::string effectId= XMLHelper::readString(effectNode, "");
            
            if(effectId != "")
            {
//                CCLOG("\t \t %s",effectId.c_str());
                EffectData* effect = EffectFactory::createEffectData(effectId.c_str());
                effectList.push_back(effect->clone());
                effect->release();
            }
            
            effectNode = effectNode->NextSiblingElement();
        }
        return effectList;
    }
    return effectList;
}

float SkillType0Parser::readTimeTick(const XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

NormalMeleeSkillData SkillType0Parser::parse(const XMLElement* root, b2World* world)
{
    NormalMeleeSkillData data;
//    data.setDamage(readDamage(root->FirstChildElement(TAG_DAMAGE)));
    data.setCoolDown(readCoolDown(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setLifeTime(readLifeTime(root->FirstChildElement(TAG_LIFE_TIME)));
    data.setSkillSensor(readBody(root->FirstChildElement(TAG_BODY), world));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
//    data.setCritical(readCriticalChance(root->FirstChildElement(TAG_CRITICAL_CHANCE)));
    data.setAnimationLayerIndex(readAnimationLayerIndex(root->FirstChildElement(TAG_ANIMATION_LAYER)));
    data.setTarget(readTarget(root->FirstChildElement(TAG_TARGET)));
    data.setTimeTick(readTimeTick(root->FirstChildElement(TAG_TIME_TICK)));

    if(root->FirstChildElement(TAG_ANIMATION) != NULL)
    {
        data.setSkillAnimation(readAnimation(root->FirstChildElement(TAG_ANIMATION)));
    }
    else
    {
        data.setSkillAnimation(NULL);
    }
    
    if(root->FirstChildElement(TAG_LIST_EFFECT) != NULL)
    {
//        CCLOG("\t %s","AFFECT ENEMY");
        data.setListEnemyEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ENEMY)));
//        if(data.getListEnemyEffect() != NULL)
//        {
//            CCLOG("%d",data.getListEnemyEffect()->count());
//        }
//        CCLOG("\t %s","AFFECT ALLIES");
        data.setListAlliesEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ALLIES)));
//        if(data.getListAlliesEffect() != NULL)
//        {
//            CCLOG("%d",data.getListAlliesEffect()->count());
//        }
    }
    return data;
}