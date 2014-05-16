//
//  SkillFactory.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/25/14.
//
//

#include "SkillFactory.h"
#include "ControllerLayer.h"
#include "NormalShootingSkillData.h"
#include "SkillType0Parser.h"
#include "SkillType1Parser.h"
#include "NormalAttack.h"
#include "SkillDTO.h"
#include "NormalShootingAttack.h"


AbstractSkill* SkillFactory::loadXMLFile(const char* id, const char *xmlFileName, b2World* world, GameObject* holder, bool isLocal, int buttonIndex)
{
    //
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    
    if (!pFileData)
    {
        CCLOG("Empty file: %s", fullPath.c_str());
        return NULL;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        //        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return NULL;
    }
    
    //Parse data
    XMLElement* root = document.FirstChildElement();
    //get child with id
    const XMLElement* result = loadElementById(id, root);
    
    if(result != NULL)
    {
        //        CCLOG("SKILL: %s",id);
        //read skill
        string type = readSkillType(result);
        AbstractSkill* normalAttack;
        
        if(strcmp(type.c_str(), SKILL_TYPE_0) == 0)
        {
            normalAttack = new NormalAttack(holder, SkillType0Parser::parse(result, world));
            
        }
        if(strcmp(type.c_str(), SKILL_TYPE_1) == 0)
        {
            
            normalAttack = new NormalShootingAttack(holder, SkillType1Parser::parse(result,world));
            
        }
        normalAttack->onCreate();
        if(isLocal)
        {
            //read texture
            std::string selectedTexture = readTextureId(result->FirstChildElement(TAG_TEXTURE), TAG_SELECTED);
            std::string activeTexture = readTextureId(result->FirstChildElement(TAG_TEXTURE), TAG_ACTIVE);
            std::string deactiveTexture = readTextureId(result->FirstChildElement(TAG_TEXTURE), TAG_DEACTIVE);
            
            TextureSelector selector;
            selector.activeTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(activeTexture.c_str());
            selector.deactiveTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(deactiveTexture.c_str());
            selector.selectedTexture = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedTexture.c_str());
            
            ControllerLayer* instance = ControllerLayer::getInstance();
            if(instance != NULL)
            {
                switch (buttonIndex)
                {
                    case SKILL_0_BUTTON:
                        instance->getAtkButtonSprite()->setTextureSelector(selector);
                        if(normalAttack!= NULL)
                        {
                            normalAttack->setholderButton(instance->getAtkButtonSprite());
                        }
                        break;
                    case SKILL_1_BUTTON:
                        instance->getSkill1ButtonSprite()->setTextureSelector(selector);
                        if(normalAttack!= NULL)
                        {
                            normalAttack->setholderButton(instance->getSkill1ButtonSprite());
                        }
                        break;
                    case SKILL_2_BUTTON:
                        instance->getSkill2ButtonSprite()->setTextureSelector(selector);
                        if(normalAttack!= NULL)
                        {
                            normalAttack->setholderButton(instance->getSkill2ButtonSprite());
                        }
                        break;
                }
            }
        }
        delete []pFileData;
        return normalAttack;
    }
    delete []pFileData;
    
    return NULL;
}

const XMLElement* SkillFactory::loadElementById(const char* id, const XMLElement* root)
{
    const XMLElement* child = root->FirstChildElement(TAG_SKILL);
    
    while(child != NULL)
    {
//        CCLOG("%s - %s",id,child->Attribute(ATTRIBUTE_ID));
        if(strcasecmp(id,child->Attribute(ATTRIBUTE_ID)) == 0)
        {
            return  child;
        }
        child = child->NextSiblingElement();
    }
    return NULL;
}

std::string SkillFactory::readSkillType(const XMLElement* root)
{
    //    if(root != NULL)
    //    {
    //        string typeValue = root->Attribute(ATTRIBUTE_TYPE);
    ////        int value = atoi(typeValue.c_str());
    ////        return value;
    //        return typeValue;
    //    }
    //    return NULL;
    return XMLHelper::readAttributeString(root, ATTRIBUTE_TYPE, "");
}

std::string SkillFactory::readTextureId(const XMLElement* root, string tagName)
{
    //    if(root != NULL)
    //    {
    //        string typeValue = root->FirstChildElement(tagName.c_str())->GetText();
    //        return typeValue;
    //    }
    //    return "";
    return XMLHelper::readString(root->FirstChildElement(tagName.c_str()), "");
}


AbstractSkill* SkillFactory::createSkill(const char* id, b2World* world, GameObject* holder, bool isLocal, int buttonIndex)
{
    AbstractSkill* skill = loadXMLFile(id, SKILL_XML_FILE, world, holder, isLocal, buttonIndex);
    skill->retain();
    return skill;
}


