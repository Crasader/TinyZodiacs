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
#include "SkillAnimationDataFactory.h"

float SkillType0Parser::readCoolDown(const XMLElement* root)
{
    return XMLHelper::readFloat(root, -1);
}

float SkillType0Parser::readLifeTime(const XMLElement* root)
{
    return XMLHelper::readFloat(root, -1);
}

JointDef SkillType0Parser::readJoinDef(const XMLElement* root)
{
    JointDef def;
    if(root != NULL)
    {
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
    return XMLHelper::readFloat(root, 0);
}

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

SkillAnimationData SkillType0Parser::readAnimationData(const XMLElement* root)
{
    SkillAnimationData data;
    data.setExcuteAnimation(NULL);
    data.setPreExcuteAnimation(NULL);
    data.setPreStopAnimation(NULL);
    data.setStopAnimation(NULL);
    if(root != NULL)
    {
        string typeValue = XMLHelper::readString(root, "");
        if(typeValue.length() ==0)
        {
            return data;
        }
        data = SkillAnimationDataFactory::loadSkillAnimationData(typeValue.c_str());
    }
    return data;
}

int SkillType0Parser::readAnimationLayerIndex(const XMLElement* root)
{
    return XMLHelper::readInt(root, ABOVE_CHARACTER_LAYER);
}

SkillTarget SkillType0Parser::readTarget(const XMLElement* root)
{
        int value = XMLHelper::readInt(root, ENEMY);
        return static_cast<SkillTarget>(value);
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

ApplyType SkillType0Parser::readApplyType(const XMLElement* root)
{
    ApplyType type = (ApplyType)XMLHelper::readInt(root, APPLY_ONCE);
    return type;
}

SkillSoundData SkillType0Parser::readSkillSoundData(const XMLElement* root)
{
    return SoundManager::loadSkillSoundData(XMLHelper::readString(root, "").c_str());
}

NormalMeleeSkillData SkillType0Parser::parse(const XMLElement* root, b2World* world)
{
    NormalMeleeSkillData data;
    data.setCoolDown(readCoolDown(root->FirstChildElement(TAG_COOL_DOWN)));
    data.setDelay(readDelay(root->FirstChildElement(TAG_DELAY)));
    data.setLifeTime(readLifeTime(root->FirstChildElement(TAG_LIFE_TIME)));
    data.setSkillSensor(readBody(root->FirstChildElement(TAG_BODY), world));
    data.setJointDefA(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_HOLDER)));
    data.setJointDefB(readJoinDef(root->FirstChildElement(TAG_JOINTS)->FirstChildElement(TAG_THIS)));
    data.setAnimationLayerIndex(readAnimationLayerIndex(root->FirstChildElement(TAG_ANIMATION_LAYER)));
    data.setTarget(readTarget(root->FirstChildElement(TAG_TARGET)));
    data.setTimeTick(readTimeTick(root->FirstChildElement(TAG_TIME_TICK)));
    data.setApplyType(readApplyType(root->FirstChildElement(TAG_APPLY_TYPE)));

    if(root->FirstChildElement(TAG_ANIMATION) != NULL)
    {
//        data.setSkillAnimation(readAnimation(root->FirstChildElement(TAG_ANIMATION)));
        data.setSkillAnimationData(readAnimationData(root->FirstChildElement(TAG_ANIMATION)));
    }
    else
    {
//        data.setSkillAnimation(NULL);
        
        SkillAnimationData data1;
        data1.setExcuteAnimation(NULL);
        data1.setPreExcuteAnimation(NULL);
        data1.setPreStopAnimation(NULL);
        data1.setStopAnimation(NULL);
        
        data.setSkillAnimationData(data1);
    }
    
    if(root->FirstChildElement(TAG_LIST_EFFECT) != NULL)
    {
        data.setListEnemyEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ENEMY)));
        data.setListAlliesEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_ALLIES)));
        data.setlistSelfEffect(readEffectList(root->FirstChildElement(TAG_LIST_EFFECT)->FirstChildElement(TAG_LIST_EFFECT_SELF)));
    }
    
    data.setSoundData(readSkillSoundData(root->FirstChildElement(TAG_SFX)));
    return data;
}