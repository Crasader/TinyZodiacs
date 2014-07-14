//
//  XMLResourcePackParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#ifndef __TinyZodiacs__XMLResourcePackParser__
#define __TinyZodiacs__XMLResourcePackParser__

class XMLResourcePackParser;
#include <iostream>
#include "ResourcePack.h"
#include "XMLHelper.h"
#include "cocos2d.h"
#include "Util.h"

USING_NS_CC;
using namespace tinyxml2;

#define TAG_RESOURCE_PACK "resource_pack"
#define ATTRIBUTE_RESOURCE_ID "id"
#define TAG_RESOURCE_PACK_LIST "resource_pack_list"


//SUB RESOURCE PACK
#define TAG_SUB_RESOURCE_PACK_LIST "sub_resource_pack_list"
#define TAG_SUB_RESOURCE_PACK "sub_resource_pack"
#define ATTRIBUTE_SUB_RESOURCE_PACK_ID "id"
#define ATTRIBUTE_SUB_RESOURCE_PACK_FILE_NAME "file_name"

//TEXTURE RESOURCE PACK
#define TAG_TEXTURE_RESOURCE_PACK_LIST "texture_resource_pack_list"
#define TAG_TEXTURE_RESOURCE_PACK "texture_resource_pack"
#define ATTRIBUTE_TEXTURE_RESOURCE_PACK_TEXTURE_NAME "texture_name"
#define ATTRIBUTE_TEXTURE_RESOURCE_PACK_PLIST_NAME "plist_name"

//XML DATA RESOURCE PACK
#define TAG_XML_DATA_PACK_LIST "xml_data_pack_list"
#define TAG_XML_DATA_PACK "xml_data_pack"
#define ATTRIBUTE_XML_DATA_TYPE "type"
#define ATTRIBUTE_XML_DATA_FILE_NAME "file_name"

class XMLResourcePackParser
{
public:
    static ResourcePack* getResourcePackFromXMLElement(XMLElement* xmlElement);
    static TextureResourcePack* getTextureResourcePackFromXMLElement(XMLElement* xmlElement);
    static XMLDataPack* getXMLDataPackFromXMLElement(XMLElement* xmlElement);

    static CCArray* getResourcePackListFromXMLElement(XMLElement* xmlElement);
    static CCArray* getTextureResourcePackListFromXMLElement(XMLElement* xmlElement);
    static CCArray* getXMLDataPackListFromXMLElement(XMLElement* xmlElement);
    static CCArray* getSubResourcePackListFromXMLElement(XMLElement* xmlElement);
    
    static ResourcePack* getResourcePackInFile(const char* resourceID, const char* fileName);
};
#endif /* defined(__TinyZodiacs__XMLResourcePackParser__) */
