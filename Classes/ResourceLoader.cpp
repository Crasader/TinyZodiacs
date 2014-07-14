//
//  TextureResourceLoader.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#include "ResourceLoader.h"

//RESOURCE LOADER

bool ResourceLoader::loadData()
{
    loadDataByFileName("resource_list.xml");
    return true;
}

bool ResourceLoader::loadDataByFileName(const char *xmlFileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(xmlFileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    CCArray* listResourcePack = XMLResourcePackParser::getResourcePackListFromXMLElement(docElement);
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(listResourcePack, object)
    {
        ResourcePack* resourcePack = static_cast<ResourcePack*>(object);
        DataCollector::getInstance()->setResourcePack(resourcePack->iD.c_str(), resourcePack);
    }
    
    delete document;

    return true;
}

bool ResourceLoader::loadResourcePackByID(const char* iD, XMLElement* root)
{

    for (XMLElement* element = root->FirstChildElement(TAG_RESOURCE_PACK); element;
         element = element->NextSiblingElement())
    {
        if(element->Attribute(ATTRIBUTE_RESOURCE_ID) != 0)
        {
            if(strcasecmp(iD, element->Attribute(ATTRIBUTE_RESOURCE_ID)) == 0)
            {
                ResourcePack* resourcePack = XMLResourcePackParser::getResourcePackFromXMLElement(element);
                if(!loadResourcePack(resourcePack))
                {
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

bool ResourceLoader::loadResourcePackByID(const char* iD, const char* fileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(fileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    if(!loadResourcePackByID(iD, docElement))
    {
        delete document;
        return false;
    }

    delete document;
    return true;
}

bool ResourceLoader::loadResourcePack(ResourcePack* resourcePack)
{
    SubResourceLoader::loadSubResourcePackList(resourcePack->listSubResourcePack);
    TextureResourceLoader::loadTextureResourcePackList(resourcePack->listTextureResourcePack);
    XMLDataLoader::loadXMLDataPackList(resourcePack->listXMLDataPack);
    return true;
}

bool ResourceLoader::loadResourcePackByIDFromDataCollector(const char* iD)
{
    ResourcePack* resourcePack = DataCollector::getInstance()->getResourcePackByKey(iD);
    return loadResourcePack(resourcePack);
}

bool ResourceLoader::unloadResourcePack(ResourcePack* resourcePack)
{
    SubResourceLoader::unloadSubResourcePackList(resourcePack->listSubResourcePack);
    TextureResourceLoader::unloadTextureResourcePackList(resourcePack->listTextureResourcePack);
    return true;
}

//SUB RESOURCE PACK LOADER
bool SubResourceLoader::loadSubResourcePack(ResourcePack* resourcePack)
{
    if(!ResourceLoader::loadResourcePack(resourcePack))
    {
        return false;
    }
    return true;
}

bool SubResourceLoader::loadSubResourcePackList(CCArray* subResourcePackList)
{
    //TEXTURE RESOURCE
    CCObject* object = NULL;
    CCARRAY_FOREACH(subResourcePackList, object)
    {
        ResourcePack* resourcePack = static_cast<ResourcePack*>(object);
        if(!SubResourceLoader::loadSubResourcePack(resourcePack))
        {
            return false;
        }
    }
    return true;
}

bool SubResourceLoader::unloadSubResourcePack(ResourcePack* resourcePack)
{
    if(!ResourceLoader::unloadResourcePack(resourcePack))
    {
        return false;
    }
    return true;
}

bool SubResourceLoader::unloadSubResourcePackList(CCArray* subResourcePackList)
{
    //TEXTURE RESOURCE
    CCObject* object = NULL;
    CCARRAY_FOREACH(subResourcePackList, object)
    {
        ResourcePack* resourcePack = static_cast<ResourcePack*>(object);
        if(!SubResourceLoader::unloadSubResourcePack(resourcePack))
        {
            return false;
        }
    }
    return true;
}

//TEXUTRE RESOURCE LOADER

bool TextureResourceLoader::loadTextureResourcePack(TextureResourcePack* textureResourcePack)
{
    CCLOG("load texture resource: %s - %s",textureResourcePack->textureName.c_str(),textureResourcePack->plistName.c_str() );
    GameManager::getInstance()->loadSpritesheet(textureResourcePack->textureName.c_str(), textureResourcePack->plistName.c_str());
    return true;
}

bool TextureResourceLoader::unloadTextureResourcePack(TextureResourcePack* textureResourcePack)
{
    CCLOG("unload texture resource: %s - %s",textureResourcePack->textureName.c_str(),textureResourcePack->plistName.c_str() );
    CCTexture2D* tex = CCTextureCache::sharedTextureCache()->textureForKey(textureResourcePack->textureName.c_str());
    if(tex != NULL)
    {
        CCLOG("%s: %d",textureResourcePack->textureName.c_str(), tex->retainCount());
        CCTextureCache::sharedTextureCache()->removeTextureForKey(textureResourcePack->textureName.c_str());
    }
   
    return true;
}

bool TextureResourceLoader::loadTextureResourcePackList(CCArray* textureResourcePackList)
{
    //TEXTURE RESOURCE
    CCObject* object = NULL;
    CCARRAY_FOREACH(textureResourcePackList, object)
    {
        TextureResourcePack* textureResourcePack = static_cast<TextureResourcePack*>(object);
        if(!TextureResourceLoader::loadTextureResourcePack(textureResourcePack))
        {
            return false;
        }
    }
   return true;
}

bool TextureResourceLoader::unloadTextureResourcePackList(CCArray* textureResourcePackList)
{
    //TEXTURE RESOURCE
    CCObject* object = NULL;
    CCARRAY_FOREACH(textureResourcePackList, object)
    {
        TextureResourcePack* textureResourcePack = static_cast<TextureResourcePack*>(object);
        if(!TextureResourceLoader::unloadTextureResourcePack(textureResourcePack))
        {
            return false;
        }
    }
    return true;
}

// XML DATA LOADER
bool XMLDataLoader::loadXMLDataPack(XMLDataPack* xMLDataPack)
{
    CCLOG("load xml data: %s - %d",xMLDataPack->fileName.c_str(), xMLDataPack->type);
    
    switch (xMLDataPack->type) {
        case XML_UNKNOWN:
            return false;
            break;
        case XML_ANIMATION:
            AnimationLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        case XML_TOWER:
            TowerLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        case XML_MAP:
            MapLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        case XML_HERO:
            HeroLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        case XML_MONSTER:
            MonsterLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        case XML_ITEM:
            ItemLoader::loadDataByFileName(xMLDataPack->fileName.c_str());
            break;
        default:
            return false;
            break;
    }
    
    return true;
}

bool XMLDataLoader::loadXMLDataPackList(CCArray* xMLDataPackList)
{
    //TEXTURE RESOURCE
    CCObject* object = NULL;
    CCARRAY_FOREACH(xMLDataPackList, object)
    {
        XMLDataPack* xMLDataPack = static_cast<XMLDataPack*>(object);
        if(!XMLDataLoader::loadXMLDataPack(xMLDataPack))
        {
            return false;
        }
    }
    return true;
}
