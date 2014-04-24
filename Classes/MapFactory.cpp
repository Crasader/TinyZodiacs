//
//  MapFactory.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/18/14.
//
//

#include "MapFactory.h"


using namespace tinyxml2;
USING_NS_CC;
static MapFactory* sharedFactory = NULL;

MapFactory::MapFactory()
{
    this->mapDTODictionary = CCDictionary::create();
    this->mapDTODictionary->retain();
}

MapFactory::~MapFactory()
{
    CC_SAFE_RELEASE(this->mapDTODictionary);
}

MapFactory* MapFactory::getSharedFactory()
{
    if (!sharedFactory)
    {
        sharedFactory = new MapFactory();
    }
    return sharedFactory;
}

bool MapFactory::loadXMLMap()
{
    loadXMLMapByNameFile("map1.xml");
    //loadXMLMapByNameFile("map2.xml");
    return true;
}

bool MapFactory::loadXMLMapByNameFile(const char *xmlFileName)
{
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        CCLOG("Empty file: %s", fullPath.c_str());
        return false;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return false;
    }
    
    XMLElement* docElement = document.FirstChildElement();
  
    MapDTO* mapDTO = XMLMapParser::XMLMapParser::getMapDTOFromXMLNode(docElement);
    
    this->mapDTODictionary->setObject(mapDTO, mapDTO->id);
    
    delete []pFileData;
    return true;
}

MapDTO* MapFactory::getMapByName(const char *mapName)
{
    return (MapDTO*)this->mapDTODictionary->objectForKey(mapName);
}
