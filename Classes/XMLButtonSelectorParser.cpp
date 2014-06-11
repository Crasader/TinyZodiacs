//
//  XMLButtonSelectorParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#include "XMLButtonSelectorParser.h"

std::string XMLButtonSelectorParser::readActiveTexture(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_ACTIVE_TEXTURE, "");
}

std::string XMLButtonSelectorParser::readDeactiveTexture(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_DEACTIVE_TEXTURE, "");
}

std::string XMLButtonSelectorParser::readSelectedTexture(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_SELECTED_TEXTURE, "");
}

TextureSelector XMLButtonSelectorParser::loadXMLFile(const char *xmlFileName, std::string selectorId)
{
    TextureSelector data ;
    
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
    XMLElement* docElement = document.FirstChildElement();
    if(docElement != NULL)
    {
        const XMLElement* result = XMLHelper::loadElementById(TAG_BUTTON, selectorId.c_str(), ATTRIBUTE_ID, docElement);
        if(result != NULL)
        {
            data.activeTexture = readActiveTexture(result);
            data.deactiveTexture = readDeactiveTexture(result);
            data.selectedTexture = readSelectedTexture(result);
        }
    }
    
    delete []pFileData;
    return data;
}

TextureSelector XMLButtonSelectorParser::parseData(std::string selectorId)
{
    return loadXMLFile("list_button_selector.xml", selectorId);
}