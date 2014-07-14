//
//  TextureResourcePack.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#ifndef __TinyZodiacs__ResourcePack__
#define __TinyZodiacs__ResourcePack__

class ResourcePack;
class TextureResourcePack;
class XMLDataPack;

#include <iostream>
#include "cocos2d.h"
#include "XMLResourcePackParser.h"
#include "PhysicConstants.h"

USING_NS_CC;
using namespace std;

class ResourcePack: public CCObject
{
private:
protected:
public:
    ResourcePack();
    ~ResourcePack();
    virtual bool init();
    
    string iD;
    string fileName;
    CCArray* listSubResourcePack;
    CCArray* listTextureResourcePack;
    CCArray* listXMLDataPack;

    CREATE_FUNC(ResourcePack);
};

class TextureResourcePack: public CCObject
{
private:
protected:
public:
    TextureResourcePack();
    ~TextureResourcePack();
    virtual bool init();
    
    string textureName;
    string plistName;
    
    CREATE_FUNC(TextureResourcePack);
};

class XMLDataPack: public CCObject
{
private:
protected:
public:
    XMLDataPack();
    ~XMLDataPack();
    virtual bool init();
    
    XMLDataType type;
    string fileName;
    
    CREATE_FUNC(XMLDataPack);
};

#endif /* defined(__TinyZodiacs__ResourcePack__) */
