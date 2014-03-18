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
    mapObjectDTO->id  = mapObjectXMLElement->Attribute("id");
    
    //image name
    mapObjectDTO->imageName = mapObjectXMLElement->Attribute("image_name");
    
    //body name
    mapObjectDTO->bodyName = mapObjectXMLElement->Attribute("body_name");
    
    XMLElement* positionXMLElement = mapObjectXMLElement->FirstChildElement("position");
    
    mapObjectDTO->x = atof(positionXMLElement->Attribute("x"));
    mapObjectDTO->y = atof(positionXMLElement->Attribute("y"));
    
    return mapObjectDTO;
}

MapDTO* XMLMapParser::getMapDTOFromXMLNode(XMLElement *mapXMLElement)
{
    MapDTO* mapDTO = MapDTO::create();
    mapDTO->retain();
    
    mapDTO->id = mapXMLElement->Attribute("id");
    mapDTO->width = atof(mapXMLElement->Attribute("width"));
    mapDTO->height = atof(mapXMLElement->Attribute("height"));
    
    //list map object
    XMLElement* mapObjectListXMLNode = mapXMLElement->FirstChildElement("map_object_list");
    
    
    for (XMLElement* element = mapObjectListXMLNode->FirstChildElement("map_object"); element; element = element->NextSiblingElement())
    {
        mapDTO->listMapObject->addObject(XMLMapParser::getMapObjectDTOFromXMLNode(element));
    }
    
    
    return mapDTO;
}