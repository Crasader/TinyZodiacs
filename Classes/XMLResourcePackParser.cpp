//
//  XMLResourcePackParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/11/14.
//
//

#include "XMLResourcePackParser.h"

ResourcePack* XMLResourcePackParser::getResourcePackFromXMLElement(XMLElement* xmlElement)
{
    ResourcePack* resourcePack = ResourcePack::create();
    
    string iD = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_RESOURCE_ID, "");
    
    resourcePack->iD = iD;
    resourcePack->listSubResourcePack->addObjectsFromArray(XMLResourcePackParser::getSubResourcePackListFromXMLElement(xmlElement->FirstChildElement(TAG_SUB_RESOURCE_PACK_LIST)));
    resourcePack->listTextureResourcePack->addObjectsFromArray(XMLResourcePackParser::getTextureResourcePackListFromXMLElement(xmlElement->FirstChildElement(TAG_TEXTURE_RESOURCE_PACK_LIST)));
    resourcePack->listXMLDataPack->addObjectsFromArray(XMLResourcePackParser::getXMLDataPackListFromXMLElement(xmlElement->FirstChildElement(TAG_XML_DATA_PACK_LIST)));
    
    return resourcePack;
}

TextureResourcePack* XMLResourcePackParser::getTextureResourcePackFromXMLElement(XMLElement* xmlElement)
{
    TextureResourcePack* textureResourcePack = TextureResourcePack::create();
    
    string textureName = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_TEXTURE_RESOURCE_PACK_TEXTURE_NAME, "");
    string plistName = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_TEXTURE_RESOURCE_PACK_PLIST_NAME, "");
    
    textureResourcePack->textureName = textureName;
    textureResourcePack->plistName = plistName;
    
    return  textureResourcePack;
}

XMLDataPack* XMLResourcePackParser::getXMLDataPackFromXMLElement(XMLElement* xmlElement)
{
    XMLDataPack* xMLDataPack = XMLDataPack::create();
    
    string type = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_XML_DATA_TYPE, "");
    string fileName = XMLHelper::readAttributeString(xmlElement, ATTRIBUTE_XML_DATA_FILE_NAME, "");
    
    xMLDataPack->type = Util::convertStringToXMLDataType(type.c_str());
    xMLDataPack->fileName = fileName;
    
    return xMLDataPack;
}

CCArray* XMLResourcePackParser::getResourcePackListFromXMLElement(XMLElement* xmlElement)
{
    CCArray* resourcePackList = CCArray::create();
    
    if (xmlElement != NULL)
    {
        for (XMLElement* element = xmlElement->FirstChildElement(TAG_RESOURCE_PACK); element; element = element->NextSiblingElement())
        {
            resourcePackList->addObject(XMLResourcePackParser::getResourcePackFromXMLElement(element));
        }
    }

    return resourcePackList;
}

CCArray* XMLResourcePackParser::getTextureResourcePackListFromXMLElement(XMLElement* xmlElement)
{
    CCArray* textureResourcePackList = CCArray::create();
    
    if (xmlElement != NULL)
    {
        for (XMLElement* element = xmlElement->FirstChildElement(TAG_TEXTURE_RESOURCE_PACK); element; element = element->NextSiblingElement())
        {
            textureResourcePackList->addObject(XMLResourcePackParser::getTextureResourcePackFromXMLElement(element));
        }
    }
    
    return textureResourcePackList;
}

CCArray* XMLResourcePackParser::getXMLDataPackListFromXMLElement(XMLElement* xmlElement)
{
    CCArray* xMLDataPackList = CCArray::create();
    
    if (xmlElement != NULL)
    {
        for (XMLElement* element = xmlElement->FirstChildElement(TAG_XML_DATA_PACK); element; element = element->NextSiblingElement())
        {
            xMLDataPackList->addObject(XMLResourcePackParser::getXMLDataPackFromXMLElement(element));
        }
    }
    
    return xMLDataPackList;
}


CCArray* XMLResourcePackParser::getSubResourcePackListFromXMLElement(XMLElement* xmlElement)
{
    CCArray* subResourcePackList = CCArray::create();
    
    if (xmlElement != NULL)
    {
        for (XMLElement* element = xmlElement->FirstChildElement(TAG_SUB_RESOURCE_PACK); element; element = element->NextSiblingElement())
        {
            string id = XMLHelper::readAttributeString(element, ATTRIBUTE_SUB_RESOURCE_PACK_ID, "");
            string fileName = XMLHelper::readAttributeString(element, ATTRIBUTE_SUB_RESOURCE_PACK_FILE_NAME, "");
            ResourcePack* resourcePack = XMLResourcePackParser::getResourcePackInFile(id.c_str(),fileName.c_str());
            if(resourcePack == NULL)
            {
                assert(0);
            }
            subResourcePackList->addObject(resourcePack);
        }
    }
    return subResourcePackList;
}

ResourcePack* XMLResourcePackParser::getResourcePackInFile(const char* resourcePackID, const char* fileName)
{
    XMLDocument* document = XMLHelper::getXMLDocument(fileName);
    
    XMLElement* docElement = document->FirstChildElement();
    
    for (XMLElement* element = docElement->FirstChildElement(TAG_RESOURCE_PACK); element; element = element->NextSiblingElement())
    {
        string id = XMLHelper::readAttributeString(element, ATTRIBUTE_RESOURCE_ID, "");
        if(strcasecmp(id.c_str(), resourcePackID) == 0)
        {
            ResourcePack* resourcePack = getResourcePackFromXMLElement(element);
            delete document;
            return resourcePack;
        }
    }
    
    delete document;
    return NULL;
}