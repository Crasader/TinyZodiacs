//
//  XMLMapParser.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/18/14.
//
//

#include "XMLMapParser.h"


MapObjectDTO* XMLMapParser::getMapObjectDTOFromXMLNode(XMLElement *mapObjectXMLElement)
{
    MapObjectDTO *mapObjectDTO = MapObjectDTO::create();
    
    //id
    mapObjectDTO->id  = mapObjectXMLElement->Attribute(MAP_OBJECT_ID);
    
    //image name
    mapObjectDTO->imageName = mapObjectXMLElement->Attribute(MAP_OBJECT_IMAGE_NAME);
    
    //body name
    mapObjectDTO->bodyName = mapObjectXMLElement->Attribute(MAP_OBJECT_BODY_NAME);
    
    XMLElement* positionXMLElement = mapObjectXMLElement->FirstChildElement(MAP_OBJECT_POSITION);
    
    mapObjectDTO->x = atof(positionXMLElement->Attribute(MAP_OBJECT_POSITION_X));
    mapObjectDTO->y = atof(positionXMLElement->Attribute(MAP_OBJECT_POSITION_Y));
    
    return mapObjectDTO;
}

MapDTO* XMLMapParser::getMapDTOFromXMLNode(XMLElement *mapXMLElement)
{
    MapDTO* mapDTO = MapDTO::create();
    mapDTO->retain();
    
    mapDTO->id = mapXMLElement->Attribute(MAP_ID);
    mapDTO->width = atof(mapXMLElement->Attribute(MAP_WIDTH));
    mapDTO->height = atof(mapXMLElement->Attribute(MAP_HEIGHT));
    
    //list map object
    XMLElement* mapObjectListXMLNode = mapXMLElement->FirstChildElement(MAP_OBJECT_LIST);
    
    for (XMLElement* element = mapObjectListXMLNode->FirstChildElement(MAP_OBJECT); element; element = element->NextSiblingElement())
    {
        mapDTO->listMapObjectDTO->addObject(XMLMapParser::getMapObjectDTOFromXMLNode(element));
    }
    
    //list background
    XMLElement* backgroundListXMLNode = mapXMLElement->FirstChildElement(BACKGROUND_LIST);
    
    for (XMLElement* element = backgroundListXMLNode->FirstChildElement(BACKGROUND); element; element = element->NextSiblingElement())
    {
        mapDTO->listBackgroundDTO->addObject(XMLMapParser::getBackgroundDTOFromXMLNode(element));
    }
    
    return mapDTO;
}

BackgroundDTO* XMLMapParser::getBackgroundDTOFromXMLNode(XMLElement *backgroundXMLElement)
{
    BackgroundDTO* backgroundDTO = BackgroundDTO::create();
    backgroundDTO->retain();
    
    backgroundDTO->imageName = backgroundXMLElement->Attribute(BACKGROUND_IMAGE_NAME);
    backgroundDTO->spritesheetName = backgroundXMLElement->Attribute(BACKGROUND_SPRITESHEET_NAME);
    backgroundDTO->ratioX = atof(backgroundXMLElement->Attribute(BACKGROUND_RATIO_X));
    backgroundDTO->ratioY = atof(backgroundXMLElement->Attribute(BACKGROUND_RATIO_Y));
    backgroundDTO->orderIndex = atof(backgroundXMLElement->Attribute(BACKGROUND_ORDER_INDEX));
    
    return backgroundDTO;
}



