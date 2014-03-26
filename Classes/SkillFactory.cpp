//
//  SkillFactory.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/25/14.
//
//

#include "SkillFactory.h"


SkillDTO SkillFactory::loadXMLFile(string id, const char *xmlFileName)
{
    
    //
    SkillDTO data;
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    //    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        //        CCLOG("Empty file: %s", fullPath.c_str());
        return data;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return data;
    }
    
    //Parse data
    XMLElement* root = document.FirstChildElement();
    const XMLElement* child = SkillFactory::loadElementById(id, root);
   
    if(child != NULL)
    {
        CCLOG("%s", child->Attribute("id"));
    }
    else
    {
        CCLOG("NULL CMNR");
    }
    
    delete []pFileData;
    return data;
}

const XMLElement* SkillFactory::loadElementById(string id, const XMLElement* root)
{
    char* tag = (char*)TAG_SKILL;
    const XMLElement* child = root->FirstChildElement(tag);
    
    do
    {
        char* id_tag = (char*)ATTRIBUTE_ID;
        if(child->Attribute(id_tag) == id.c_str())
        {
            return child;
        }
        child = child->NextSiblingElement();
    }
    while(child -> NextSiblingElement() != NULL);
    return NULL;
}


AbstractSkill* SkillFactory::createSkill(string id, b2World* world, GameObject* holder)
{
    loadXMLFile(id, "list_skill.xml");
    return NULL;
}


