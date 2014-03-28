//
//  SkillFactory.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/25/14.
//
//

#include "SkillFactory.h"


AbstractSkill* SkillFactory::loadXMLFile(const char* id, const char *xmlFileName, b2World* world, GameObject* holder)
{
    //
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    //    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        //        CCLOG("Empty file: %s", fullPath.c_str());
        return NULL;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return NULL;
    }
    
    //Parse data
    XMLElement* root = document.FirstChildElement();
    
    //get child with id
    const XMLElement* result = loadElementById(id, root);
    
    if(result != NULL)
    {
        int type = readSkillType(result);
        CCLOG("type %d",type);
        
        switch (type) {
            case SKILL_TYPE_0:
                NormalAttack* normalAttack = new NormalAttack(holder, SkillType0Parser::parse(result, world));
                return normalAttack;
                break;
        }
    }
    delete []pFileData;
    return NULL;
}

const XMLElement* SkillFactory::loadElementById(const char* id, const XMLElement* root)
{
    const XMLElement* child = root->FirstChildElement(TAG_SKILL);
    while(child != NULL)
    {
        if(strcmp(id, child->Attribute(ATTRIBUTE_ID))==0)
        {
            return  child;
        }
        child = child->NextSiblingElement();
    }
    return NULL;
}

int SkillFactory::readSkillType(const XMLElement* root)
{
    if(root != NULL)
    {
        string typeValue = root->Attribute(ATTRIBUTE_ID);
        int value = atoi(typeValue.c_str());
        return value;
    }
    return -1;
}

AbstractSkill* SkillFactory::createSkill(const char* id, b2World* world, GameObject* holder)
{
    return loadXMLFile(id, "list_skill.xml", world, holder);
}


