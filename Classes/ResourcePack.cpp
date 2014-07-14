//
//  TextureResourcePack.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#include "ResourcePack.h"

//RESOURCE PACK
ResourcePack::ResourcePack()
{
    this->listSubResourcePack = CCArray::create();
    this->listSubResourcePack->retain();
    this->listTextureResourcePack = CCArray::create();
    this->listTextureResourcePack->retain();
    this->listXMLDataPack = CCArray::create();
    this->listXMLDataPack->retain();
}

ResourcePack::~ResourcePack()
{
    this->listSubResourcePack->release();
    this->listTextureResourcePack->release();
    this->listXMLDataPack->release();
}

bool ResourcePack::init()
{
    return true;
}

// TEXTURE RESOURCE PACK
TextureResourcePack::TextureResourcePack()
{
    
}

TextureResourcePack::~TextureResourcePack()
{
    
}

bool TextureResourcePack::init()
{
    return true;
}

// XML DATA PACK
XMLDataPack::XMLDataPack()
{
    this->type = XML_UNKNOWN;
}

XMLDataPack::~XMLDataPack()
{
    
}

bool XMLDataPack::init()
{
    return true;
}