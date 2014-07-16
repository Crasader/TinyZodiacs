//
//  ResourceManager.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/15/14.
//
//

#include "ResourceManager.h"

static ResourceManager* instance = NULL;

ResourceManager::ResourceManager()
{
    this->unusedResourcePackList = CCArray::create();
    this->unusedResourcePackList->retain();
}

ResourceManager::~ResourceManager()
{
    this->unusedResourcePackList->release();
}

ResourceManager* ResourceManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::clean()
{
    
}
