//
//  TextureResourceLoader.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#ifndef __TinyZodiacs__ResourceLoader__
#define __TinyZodiacs__ResourceLoader__

#include <iostream>
#include "XMLHelper.h"
#include "DataCollector.h"
#include "XMLItemParser.h"
#include "XMLResourcePackParser.h"
#include "GameManager.h"
#include "HeroLoader.h"
#include "MapLoader.h"
#include "ItemLoader.h"
#include "MonsterLoader.h"
#include "TowerLoader.h"
#include "AnimationLoader.h"

using namespace tinyxml2;
using namespace std;
//RESOURCE LOADER
class ResourceLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
    static bool loadResourcePackByID(const char* iD, XMLElement* root);
    static bool loadResourcePackByID(const char* iD, const char* fileName);
    static bool loadResourcePack(ResourcePack* resourcePack);
    static bool loadResourcePackByIDFromDataCollector(const char* iD);
    
    static bool unloadResourcePack(ResourcePack* resourcePack);
};

//TEXTURE RESOURCE LOADER
class SubResourceLoader
{
private:
protected:
public:
    static bool loadSubResourcePack(ResourcePack* resourcePack);
    static bool loadSubResourcePackList(CCArray* subResourcePackList);
    static bool unloadSubResourcePack(ResourcePack* resourcePack);
    static bool unloadSubResourcePackList(CCArray* subResourcePackList);
};

//TEXTURE RESOURCE LOADER
class TextureResourceLoader
{
private:
protected:
public:
    static bool loadTextureResourcePack(TextureResourcePack* textureResourcePack);
    static bool unloadTextureResourcePack(TextureResourcePack* textureResourcePack);
    static bool loadTextureResourcePackList(CCArray* TextureResourcePackList);
    static bool unloadTextureResourcePackList(CCArray* TextureResourcePackList);
};

//XML DATA LOADER
class XMLDataLoader
{
private:
protected:
public:
    static bool loadXMLDataPack(XMLDataPack* xMLDataPack);
    static bool loadXMLDataPackList(CCArray* xMLDataPackList);
};




#endif /* defined(__TinyZodiacs__TextureResourceLoader__) */
