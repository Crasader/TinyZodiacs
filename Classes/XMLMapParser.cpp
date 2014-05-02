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
    
    //list monster factory
    XMLElement* monsterFactoryListXMLNode = mapXMLElement->FirstChildElement(TAG_MONSTER_FACTORY_LIST);
    
    for (XMLElement* element = monsterFactoryListXMLNode->FirstChildElement(TAG_MONSTER_FACTORY); element; element = element->NextSiblingElement())
    {
        mapDTO->listMonsterFactoryDTO->addObject(XMLMapParser::getMonsterFactoryDTOFromXMLNode(element));
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
        
        vector<string> listLaneString  = Util::getStrTok(laneXMLElement->GetText());
        for(int i = 0; i < listLaneString.size(); i++)
        {
            sensorObjectDTO->listLaneID.push_back(atoi(listLaneString[i].c_str()));
        }
        
    }
    return sensorObjectDTO;
}

TowerDTO* XMLMapParser::getTowerDTOFromXMLNode(XMLElement* towerXMLElement)
{
    TowerDTO* towerDTO = TowerDTO::create();
    
    towerDTO->id = towerXMLElement->Attribute(ATTRIBUTE_TOWER_ID);
    towerDTO->group = towerXMLElement->Attribute(ATTRIBUTE_TOWER_GROUP);
    
    //position
    if(towerXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = towerXMLElement->FirstChildElement(TAG_POSITION);
        
        towerDTO->positionX = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        towerDTO->positionY = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    return towerDTO;
}

MonsterCreatorDTO* XMLMapParser::getMonsterCreatorDTOFromXMLNode(XMLElement* monsterCreatorXMLElement)
{
    MonsterCreatorDTO* monsterCreatorDTO = MonsterCreatorDTO::create();
    
    monsterCreatorDTO->delay = atof(monsterCreatorXMLElement->Attribute(ATTRIBUTE_MONSTER_CREATOR_DELAY));
    monsterCreatorDTO->delayPerUnit = atof(monsterCreatorXMLElement->Attribute(ATTRIBUTE_MONSTER_CREATOR_DELAY_PER_UNIT));
    
    //position
    if(monsterCreatorXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = monsterCreatorXMLElement->FirstChildElement(TAG_POSITION);
        
        monsterCreatorDTO->positionX = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        monsterCreatorDTO->positionY = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    if(monsterCreatorXMLElement->FirstChildElement(TAG_MONSTER) != NULL)
    {
        XMLElement* monsterXMLElement = monsterCreatorXMLElement->FirstChildElement(TAG_MONSTER);
        
        std::vector<string> listMonsterIDString = Util::getStrTok(monsterXMLElement->GetText());
        for(int i = 0; i < listMonsterIDString.size(); i++)
        {
            monsterCreatorDTO->listMonsterID.push_back(listMonsterIDString[i]);
        }
    }
    
    return monsterCreatorDTO;
}

MonsterFactoryDTO* XMLMapParser::getMonsterFactoryDTOFromXMLNode(XMLElement* monsterFactoryXMLElement)
{
    MonsterFactoryDTO* monsterFactoryDTO = MonsterFactoryDTO::create();
    
    std::string group = std::string(monsterFactoryXMLElement->Attribute(ATTRIBUTE_MONSTER_FACTORY_GROUP));
    
    if (strcasecmp(group.c_str(), "A") == 0) {
        monsterFactoryDTO->group = A;
    }
    else if(strcasecmp(group.c_str(), "B") == 0)
    {
        monsterFactoryDTO->group = B;
    }
    
    //monster creator
    for (XMLElement* element = monsterFactoryXMLElement->FirstChildElement(TAG_MONSTER_CREATOR); element; element = element->NextSiblingElement())
    {
        monsterFactoryDTO->listMonsterCreatorDTO->addObject(XMLMapParser::getMonsterCreatorDTOFromXMLNode(element));
    }
    
    return monsterFactoryDTO;
}

