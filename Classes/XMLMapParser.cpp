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
    if(mapObjectXMLElement->Attribute(MAP_OBJECT_BODY_NAME) != NULL)
        mapObjectDTO->bodyName = mapObjectXMLElement->Attribute(MAP_OBJECT_BODY_NAME);
    
    mapObjectDTO->layerIndex = atof(mapObjectXMLElement->Attribute(LAYER_INDEX));
    
    if(mapObjectXMLElement->FirstChildElement(POSITION) != NULL)
    {
        XMLElement* positionXMLElement = mapObjectXMLElement->FirstChildElement(POSITION);
    
        mapObjectDTO->x = atof(positionXMLElement->Attribute(POSITION_X));
        mapObjectDTO->y = atof(positionXMLElement->Attribute(POSITION_Y));
    }
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
    
    //list foreground
    XMLElement* foregroundListXMLNode = mapXMLElement->FirstChildElement(FOREGROUND_LIST);
    
    for (XMLElement* element = foregroundListXMLNode->FirstChildElement(FOREGROUND); element; element = element->NextSiblingElement())
    {
        mapDTO->listForegroundDTO->addObject(XMLMapParser::getForegroundDTOFromXMLNode(element));
    }
    
    return mapDTO;
}

BackgroundDTO* XMLMapParser::getBackgroundDTOFromXMLNode(XMLElement *backgroundXMLElement)
{
    BackgroundDTO* backgroundDTO = BackgroundDTO::create();
    backgroundDTO->retain();
    
    backgroundDTO->imageName = backgroundXMLElement->Attribute(BACKGROUND_IMAGE_NAME);
    backgroundDTO->spritesheetName = backgroundXMLElement->Attribute(BACKGROUND_SPRITESHEET_NAME);
    
    XMLElement* ratioElement = backgroundXMLElement->FirstChildElement(RATIO);
    backgroundDTO->ratioX = atof(ratioElement->Attribute(RATIO_X));
    backgroundDTO->ratioY = atof(ratioElement->Attribute(RATIO_Y));
    backgroundDTO->orderIndex = atof(backgroundXMLElement->Attribute(LAYER_INDEX));
    
    return backgroundDTO;
}

ForegroundDTO* XMLMapParser::getForegroundDTOFromXMLNode(XMLElement* foregroundXMLElement)
{
    ForegroundDTO* foregroundDTO = ForegroundDTO::create();
    foregroundDTO->retain();
    
    foregroundDTO->imageName = foregroundXMLElement->Attribute(FOREGROUND_IMAGE_NAME);
    foregroundDTO->layerIndex = atof(foregroundXMLElement->Attribute(LAYER_INDEX));
    
    XMLElement* ratioElement = foregroundXMLElement->FirstChildElement(RATIO);
    foregroundDTO->ratioX = atof(ratioElement->Attribute(RATIO_X));
    foregroundDTO->ratioY = atof(ratioElement->Attribute(RATIO_Y));
 
    
    XMLElement* positionElement = foregroundXMLElement->FirstChildElement(POSITION);
    foregroundDTO->positionX = atof(positionElement->Attribute(POSITION_X));
    foregroundDTO->positionY = atof(positionElement->Attribute(POSITION_Y));

    
    return foregroundDTO;
}



