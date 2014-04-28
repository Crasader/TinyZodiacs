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
    mapObjectDTO->id  = mapObjectXMLElement->Attribute(ATTRIBUTE_MAP_OBJECT_ID);
    
    //image name
    mapObjectDTO->imageName = mapObjectXMLElement->Attribute(ATTRIBUTE_MAP_OBJECT_IMAGE_NAME);
    
    //body name
    if(mapObjectXMLElement->Attribute(ATTRIBUTE_MAP_OBJECT_BODY_NAME) != NULL)
        mapObjectDTO->bodyName = mapObjectXMLElement->Attribute(ATTRIBUTE_MAP_OBJECT_BODY_NAME);
    
    mapObjectDTO->layerIndex = atof(mapObjectXMLElement->Attribute(ATTRIBUTE_LAYER_INDEX));
    
    //position
    if(mapObjectXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = mapObjectXMLElement->FirstChildElement(TAG_POSITION);
        
        mapObjectDTO->x = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        mapObjectDTO->y = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    //can pass
    if(mapObjectXMLElement->FirstChildElement(TAG_CAN_PASS) != NULL)
    {
        mapObjectDTO->canPass = strcasecmp("false", mapObjectXMLElement->FirstChildElement(TAG_CAN_PASS)->GetText());
    }
    return mapObjectDTO;
}

MapDTO* XMLMapParser::getMapDTOFromXMLNode(XMLElement *mapXMLElement)
{
    MapDTO* mapDTO = MapDTO::create();
    
    mapDTO->id = mapXMLElement->Attribute(ATTRIBUTE_MAP_ID);
    mapDTO->width = atof(mapXMLElement->Attribute(ATTRIBUTE_MAP_WIDTH));
    mapDTO->height = atof(mapXMLElement->Attribute(ATTRIBUTE_MAP_HEIGHT));
    
    //list map object
    XMLElement* mapObjectListXMLNode = mapXMLElement->FirstChildElement(TAG_MAP_OBJECT_LIST);
    
    for (XMLElement* element = mapObjectListXMLNode->FirstChildElement(TAG_MAP_OBJECT); element; element = element->NextSiblingElement())
    {
        mapDTO->listMapObjectDTO->addObject(XMLMapParser::getMapObjectDTOFromXMLNode(element));
    }
    
    //list background
    XMLElement* backgroundListXMLNode = mapXMLElement->FirstChildElement(TAG_BACKGROUND_LIST);
    
    for (XMLElement* element = backgroundListXMLNode->FirstChildElement(TAG_BACKGROUND); element; element = element->NextSiblingElement())
    {
        mapDTO->listBackgroundDTO->addObject(XMLMapParser::getBackgroundDTOFromXMLNode(element));
    }
    
    //list foreground
    XMLElement* foregroundListXMLNode = mapXMLElement->FirstChildElement(TAG_FOREGROUND_LIST);
    
    for (XMLElement* element = foregroundListXMLNode->FirstChildElement(TAG_FOREGROUND); element; element = element->NextSiblingElement())
    {
        mapDTO->listForegroundDTO->addObject(XMLMapParser::getForegroundDTOFromXMLNode(element));
    }
    
    //list sensor
    XMLElement* sensorListXMLNode = mapXMLElement->FirstChildElement(TAG_SENSOR_OBJECT_LIST);
    
    for (XMLElement* element = sensorListXMLNode->FirstChildElement(TAG_SENSOR_OBJECT); element; element = element->NextSiblingElement())
    {
        mapDTO->listSensorObjectDTO->addObject(XMLMapParser::getSensorObjectDTOFromXMLNode(element));
    }

    //list tower
    XMLElement* towerListXMLNode = mapXMLElement->FirstChildElement(TAG_TOWER_LIST);
    
    for (XMLElement* element = towerListXMLNode->FirstChildElement(TAG_TOWER); element; element = element->NextSiblingElement())
    {
        mapDTO->listTowerDTO->addObject(XMLMapParser::getTowerDTOFromXMLNode(element));
    }

    return mapDTO;
}

BackgroundDTO* XMLMapParser::getBackgroundDTOFromXMLNode(XMLElement *backgroundXMLElement)
{
    BackgroundDTO* backgroundDTO = BackgroundDTO::create();
    
    backgroundDTO->imageName = backgroundXMLElement->Attribute(ATTRIBUTE_BACKGROUND_IMAGE_NAME);
    backgroundDTO->spritesheetName = backgroundXMLElement->Attribute(ATTRIBUTE_BACKGROUND_SPRITESHEET_NAME);
    
    XMLElement* ratioElement = backgroundXMLElement->FirstChildElement(TAG_RATIO);
    backgroundDTO->ratioX = atof(ratioElement->Attribute(ATTRIBUTE_RATIO_X));
    backgroundDTO->ratioY = atof(ratioElement->Attribute(ATTRIBUTE_RATIO_Y));
    backgroundDTO->orderIndex = atof(backgroundXMLElement->Attribute(ATTRIBUTE_LAYER_INDEX));
    
    return backgroundDTO;
}

ForegroundDTO* XMLMapParser::getForegroundDTOFromXMLNode(XMLElement* foregroundXMLElement)
{
    ForegroundDTO* foregroundDTO = ForegroundDTO::create();
    
    foregroundDTO->imageName = foregroundXMLElement->Attribute(ATTRIBUTE_FOREGROUND_IMAGE_NAME);
    foregroundDTO->layerIndex = atof(foregroundXMLElement->Attribute(ATTRIBUTE_LAYER_INDEX));
    
    XMLElement* ratioElement = foregroundXMLElement->FirstChildElement(TAG_RATIO);
    foregroundDTO->ratioX = atof(ratioElement->Attribute(ATTRIBUTE_RATIO_X));
    foregroundDTO->ratioY = atof(ratioElement->Attribute(ATTRIBUTE_RATIO_Y));
    
    
    XMLElement* positionElement = foregroundXMLElement->FirstChildElement(TAG_POSITION);
    foregroundDTO->positionX = atof(positionElement->Attribute(ATTRIBUTE_POSITION_X));
    foregroundDTO->positionY = atof(positionElement->Attribute(ATTRIBUTE_POSITION_Y));
    
    return foregroundDTO;
}

SensorObjectDTO* XMLMapParser::getSensorObjectDTOFromXMLNode(XMLElement* sensorObjectXMLElement)
{
    SensorObjectDTO *sensorObjectDTO = SensorObjectDTO::create();
    
    
    sensorObjectDTO->isBack = strcasecmp("false", sensorObjectXMLElement->Attribute(ATTRIBUTE_SENSOR_OBJECT_ISBACK));
    sensorObjectDTO->mustStop = strcasecmp("false", sensorObjectXMLElement->Attribute(ATTRIBUTE_SENSOR_OBJECT_MUSTSTOP));
    sensorObjectDTO->moveSpeed = atof(sensorObjectXMLElement->Attribute(ATTRIBUTE_SENSOR_OBJECT_MOVE_SPEED));
    sensorObjectDTO->jumpHeight = atof(sensorObjectXMLElement->Attribute(ATTRIBUTE_SENSOR_OBJECT_JUMP_HEIGHT));
    
    const char* direc = sensorObjectXMLElement->Attribute(ATTRIBUTE_SENSOR_OBJECT_DIRECTION);
    
    if(strcasecmp(direc, "left")==0)
    {
        sensorObjectDTO->direction = LEFT;
    }
    else
    {
        sensorObjectDTO->direction = RIGHT;
    }
    
    //position
    if(sensorObjectXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = sensorObjectXMLElement->FirstChildElement(TAG_POSITION);
        
        sensorObjectDTO->x = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        sensorObjectDTO->y = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    
    if(sensorObjectXMLElement->FirstChildElement(TAG_EDGE) != NULL)
    {
        XMLElement* positionXMLElement = sensorObjectXMLElement->FirstChildElement(TAG_EDGE);
        
        sensorObjectDTO->edge_x = atof(positionXMLElement->Attribute(ATTRIBUTE_EDGE_X));
        sensorObjectDTO->edge_y = atof(positionXMLElement->Attribute(ATTRIBUTE_EDGE_Y));
    }
    
    if(sensorObjectXMLElement->FirstChildElement(TAG_LANE) != NULL)
    {
        XMLElement* laneXMLElement = sensorObjectXMLElement->FirstChildElement(TAG_LANE);
        //
        char* laneString = (char*)laneXMLElement->GetText();
        
        if(laneString!=NULL)
        {
            char buffer[128] = {0};
            int count = 0;
            for(int i=0;i<strlen(laneString);i++)
            {
                if(laneString[i] != ' ')
                {
                    buffer[count] = laneString[i];
                    count++;
                }
            }
            
            const char s[2] = ",";
            
            char *token;
            
            /* get the first token */
            token = std::strtok(buffer, s);
            
            /* walk through other tokens */
            while( token != NULL )
            {
                sensorObjectDTO->listLaneID.push_back(atoi(token));
                token = strtok(NULL, s);
            }
        }
    }
    return sensorObjectDTO;
}

TowerDTO* XMLMapParser::getTowerDTOFromXMLNode(XMLElement* towerXMLElement)
{
    TowerDTO *towerDTO = TowerDTO::create();
    
    towerDTO->id = towerXMLElement->Attribute(ATTRIBUTE_TOWER_ID);
    towerDTO->group = towerXMLElement->Attribute(ATTRIBUTE_TOWER_GROUP);

    //position
    if(towerXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = towerXMLElement->FirstChildElement(TAG_POSITION);
        
        towerDTO->x = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        towerDTO->y = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    return towerDTO;
}



