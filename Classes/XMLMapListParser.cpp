//
//  XMLMapListParser.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "XMLMapListParser.h"
#include "XMLHelper.h"

#define TAG_MAP "map"

#define ATTRIBUTE_STATE "state"
#define ATTRIBUTE_NORMAL_ICON "normal_icon"
#define ATTRIBUTE_SELECTED_ICON "selected_icon"
#define ATTRIBUTE_ID "id"

std::vector<MapSelectData> XMLMapListParser::loadXMLFile(const char *xmlFileName)
{
    
    std::vector<MapSelectData> data ;
    
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
        for(XMLElement* child = docElement->FirstChildElement(TAG_MAP) ; child!=NULL ; child = child->NextSiblingElement())
        {
            MapSelectData mdata;
            
            TextureSelector selector;
            selector.activeTexture = selector.deactiveTexture = readNormalIcon(child);
            selector.selectedTexture = readSelectedIcon(child);
            mdata.setSelector(selector);
            
            mdata.setID(readID(child));
            mdata.setstate(readState(child));
            
            data.push_back(mdata);
        }
    }
    
    delete []pFileData;
    return data;
}

std::vector<MapSelectData> XMLMapListParser::getMapList()
{
    return loadXMLFile("list_map.xml");
}

std::string XMLMapListParser::readID(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_ID, "");
}

std::string XMLMapListParser::readNormalIcon(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_NORMAL_ICON, "");
}

std::string XMLMapListParser::readSelectedIcon(const XMLElement* root)
{
    return XMLHelper::readAttributeString(root, ATTRIBUTE_SELECTED_ICON, "");
}

bool XMLMapListParser::readState(const XMLElement* root)
{
    return XMLHelper::readAttributeInt(root, ATTRIBUTE_STATE, 0);
}