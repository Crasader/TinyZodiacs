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
    
    
    mapDTO->listSensorObjectDTO->addObjectsFromArray(getSensorObjectDTOListFromXMLElement(mapXMLElement));
    mapDTO->listTowerStructDTO->addObjectsFromArray(getTowerStructDTOListFromXMLElement(mapXMLElement));
    mapDTO->listMonsterFactoryDTO->addObjectsFromArray(getMonsterFactoryDTOListFromXMLElement(mapXMLElement));
    mapDTO->listItemCreatorDTO->addObjectsFromArray(getItemCreatorDTOListFromXMLElement(mapXMLElement));
    mapDTO->listWaveDTO->addObjectsFromArray(getWaveDTOListFromXMLElement(mapXMLElement));
    mapDTO->listWallDTO->addObjectsFromArray(getWallDTOListFromXMLElement(mapXMLElement));
    
    CCPoint revivePosition = getHeroRevivePositionFromXMLElement(mapXMLElement);
    mapDTO->revivePositionX = revivePosition.x;
    mapDTO->revivePositionY = revivePosition.y;
    
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

TowerStructDTO* XMLMapParser::getTowerStructDTOFromXMLNode(XMLElement* towerXMLElement)
{
    TowerStructDTO* towerStructDTO = TowerStructDTO::create();
    
    towerStructDTO->id = towerXMLElement->Attribute(ATTRIBUTE_TOWER_ID);
    
    string groupString = towerXMLElement->Attribute(ATTRIBUTE_TOWER_GROUP);
    if(strcasecmp(groupString.c_str(), "A") == 0)
    {
        towerStructDTO->group = A;
    }
    else
    {
        towerStructDTO->group = B;
    }
    towerStructDTO->type = XMLHelper::readAttributeString(towerXMLElement, "type", "");
    //position
    if(towerXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = towerXMLElement->FirstChildElement(TAG_POSITION);
        
        towerStructDTO->positionX = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        towerStructDTO->positionY = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    return towerStructDTO;
}

MonsterCreatorDTO* XMLMapParser::getMonsterCreatorDTOFromXMLNode(XMLElement* monsterCreatorXMLElement)
{
    MonsterCreatorDTO* monsterCreatorDTO = MonsterCreatorDTO::create();
    
    monsterCreatorDTO->delay = atof(monsterCreatorXMLElement->Attribute(ATTRIBUTE_MONSTER_CREATOR_DELAY));
    monsterCreatorDTO->delayPerUnit = atof(monsterCreatorXMLElement->Attribute(ATTRIBUTE_MONSTER_CREATOR_DELAY_PER_UNIT));
    monsterCreatorDTO->laneID = atoi(monsterCreatorXMLElement->Attribute(ATTRIBUTE_MONSTER_CREATOR_LANE));
    
    //position
    if(monsterCreatorXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = monsterCreatorXMLElement->FirstChildElement(TAG_POSITION);
        
        monsterCreatorDTO->positionX = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        monsterCreatorDTO->positionY = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    XMLElement* monsterListXMLElement = monsterCreatorXMLElement->FirstChildElement(TAG_MONSTER_LIST);
    if(monsterListXMLElement != NULL)
    {
        for (XMLElement* element = monsterListXMLElement->FirstChildElement(TAG_MONSTER); element; element = element->NextSiblingElement())
        {
            string monsterID = XMLHelper::readAttributeString(element, ATTRIBUTE_MONSTER_ID, "");
            int quantity = XMLHelper::readAttributeInt(element, ATTRIBUTE_MONSTER_QUANTITY, 0);
            
            for (int i = 0; i < quantity; i++)
            {
                monsterCreatorDTO->listMonsterID.push_back(monsterID);
            }
        }
    }
    
    
    
    
    //    if(monsterCreatorXMLElement->FirstChildElement(TAG_MONSTER) != NULL)
    //    {
    //        XMLElement* monsterXMLElement = monsterCreatorXMLElement->FirstChildElement(TAG_MONSTER);
    //
    //        std::vector<string> listMonsterIDString = Util::getStrTok(monsterXMLElement->GetText());
    //        for(int i = 0; i < listMonsterIDString.size(); i++)
    //        {
    //            monsterCreatorDTO->listMonsterID.push_back(listMonsterIDString[i]);
    //        }
    //    }
    
    return monsterCreatorDTO;
}



MonsterFactoryDTO* XMLMapParser::getMonsterFactoryDTOFromXMLNode(XMLElement* monsterFactoryXMLElement)
{
    MonsterFactoryDTO* monsterFactoryDTO = MonsterFactoryDTO::create();
    
    std::string group = std::string(monsterFactoryXMLElement->Attribute(ATTRIBUTE_MONSTER_FACTORY_GROUP));
    int max = XMLHelper::readAttributeInt(monsterFactoryXMLElement, ATTRIBUTE_MONSTER_FACTORY_MAX, INFINITY);
    
    if (strcasecmp(group.c_str(), "A") == 0) {
        monsterFactoryDTO->group = A;
    }
    else if(strcasecmp(group.c_str(), "B") == 0)
    {
        monsterFactoryDTO->group = B;
    }
    monsterFactoryDTO->max = max;
    
    //monster creator
    for (XMLElement* element = monsterFactoryXMLElement->FirstChildElement(TAG_MONSTER_CREATOR); element; element = element->NextSiblingElement())
    {
        monsterFactoryDTO->listMonsterCreatorDTO->addObject(XMLMapParser::getMonsterCreatorDTOFromXMLNode(element));
    }
    
    return monsterFactoryDTO;
}

ItemCreatorDTO* XMLMapParser::getItemCreatorDTOFromXMLNode(XMLElement* itemCreatorXMLElement)
{
    ItemCreatorDTO* itemCreatorDTO = ItemCreatorDTO::create();
    
    int max = XMLHelper::readAttributeInt(itemCreatorXMLElement, ATTRIBUTE_ITEM_CREATOR_MAX, 0);
    float delayMin = XMLHelper::readAttributeFloat(itemCreatorXMLElement, ATTRIBUTE_ITEM_CREATOR_DELAY_MIN, 0);
    float delayMax = XMLHelper::readAttributeFloat(itemCreatorXMLElement, ATTRIBUTE_ITEM_CREATOR_DELAY_MAX, 0);
    float beginPositionX;
    float beginPositionY;
    float endPositionX;
    float endPositionY;
    
    XMLElement* beginPositionXMLElement = itemCreatorXMLElement->FirstChildElement(TAG_ITEM_CREATOR_BEGIN_POSITION);
    if(beginPositionXMLElement != NULL)
    {
        beginPositionX = XMLHelper::readAttributeFloat(beginPositionXMLElement, ATTRIBUTE_POSITION_X, 0);
        beginPositionY = XMLHelper::readAttributeFloat(beginPositionXMLElement, ATTRIBUTE_POSITION_Y, 0);
    }
    
    XMLElement* endPositionXMLElement = itemCreatorXMLElement->FirstChildElement(TAG_ITEM_CREATOR_END_POSITION);
    if(endPositionXMLElement != NULL)
    {
        endPositionX = XMLHelper::readAttributeFloat(endPositionXMLElement, ATTRIBUTE_POSITION_X, 0);
        endPositionY = XMLHelper::readAttributeFloat(endPositionXMLElement, ATTRIBUTE_POSITION_Y, 0);
    }
    
    itemCreatorDTO->max = max;
    itemCreatorDTO->delayMin = delayMin;
    itemCreatorDTO->delayMax = delayMax;
    itemCreatorDTO->beginPositionX = beginPositionX;
    itemCreatorDTO->beginPositionY = beginPositionY;
    itemCreatorDTO->endPositionX = endPositionX;
    itemCreatorDTO->endPositionY = endPositionY;
    itemCreatorDTO->listItem = XMLItemParser::getSubItemStructListFromXMLElement(itemCreatorXMLElement);
    
    return itemCreatorDTO;
}

WaveDTO* XMLMapParser::getWaveFromXMLNode(XMLElement* waveXMLElement)
{
    WaveDTO* waveDTO = WaveDTO::create();
    
    string name = XMLHelper::readAttributeString(waveXMLElement, ATTRIBUTE_WAVE_NAME, "");
    //list monster factory
    
    waveDTO->listMonsterFactoryDTO->addObjectsFromArray(XMLMapParser::getMonsterFactoryDTOListFromXMLElement(waveXMLElement));
    waveDTO->listItemCreatorDTO->addObjectsFromArray(XMLMapParser::getItemCreatorDTOListFromXMLElement(waveXMLElement));
    waveDTO->waveMusicID = XMLHelper::readAttributeString(waveXMLElement, ATTRIBUTE_WAVE_MUSIC, "");
    waveDTO->name = name;
    
    return waveDTO;
}

WallDTO* XMLMapParser::getWallDTOFromXMLNode(XMLElement* wallXMLElement)
{
    WallDTO *wallDTO = WallDTO::create();
    
    bool deadWall = XMLHelper::readAttributeBoolString(wallXMLElement, ATTRIBUTE_WALL_DEADWALL, false);
    //position
    if(wallXMLElement->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = wallXMLElement->FirstChildElement(TAG_POSITION);
        
        wallDTO->x = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        wallDTO->y = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    if(wallXMLElement->FirstChildElement(TAG_EDGE) != NULL)
    {
        XMLElement* positionXMLElement = wallXMLElement->FirstChildElement(TAG_EDGE);
        
        wallDTO->edge_x = atof(positionXMLElement->Attribute(ATTRIBUTE_EDGE_X));
        wallDTO->edge_y = atof(positionXMLElement->Attribute(ATTRIBUTE_EDGE_Y));
    }
    
    wallDTO->deadWall = deadWall;
    
    return wallDTO;
}

CCArray* XMLMapParser::getMonsterFactoryDTOListFromXMLElement(XMLElement* root)
{
    CCArray* monsterFactoryList = CCArray::create();
    
    XMLElement* monsterFactoryListXMLElement = root->FirstChildElement(TAG_MONSTER_FACTORY_LIST);
    
    if(monsterFactoryListXMLElement != NULL)
    {
        for (XMLElement* element = monsterFactoryListXMLElement->FirstChildElement(TAG_MONSTER_FACTORY); element; element = element->NextSiblingElement())
        {
            monsterFactoryList->addObject(XMLMapParser::getMonsterFactoryDTOFromXMLNode(element));
        }
    }
    
    return monsterFactoryList;
}


CCArray* XMLMapParser::getItemCreatorDTOListFromXMLElement(XMLElement* root)
{
    CCArray* itemCreatorList = CCArray::create();
    
    XMLElement* itemCreatorListXMLElement = root->FirstChildElement(TAG_ITEM_CREATOR_LIST);
    
    if (itemCreatorListXMLElement != NULL)
    {
        for (XMLElement* element = itemCreatorListXMLElement->FirstChildElement(TAG_ITEM_CREATOR); element; element = element->NextSiblingElement())
        {
            itemCreatorList->addObject(XMLMapParser::getItemCreatorDTOFromXMLNode(element));
        }
    }
    
    return itemCreatorList;
}

CCArray* XMLMapParser::getWaveDTOListFromXMLElement(XMLElement* root)
{
    CCArray* waveList = CCArray::create();
    
    XMLElement* waveListXMLNode = root->FirstChildElement(TAG_WAVE_LIST);
    
    if(waveListXMLNode != NULL)
    {
        for (XMLElement* element = waveListXMLNode->FirstChildElement(TAG_WAVE); element; element = element->NextSiblingElement())
        {
            waveList->addObject(XMLMapParser::getWaveFromXMLNode(element));
        }
    }
    return waveList;
}


CCArray* XMLMapParser::getTowerStructDTOListFromXMLElement(XMLElement* root)
{
    CCArray* towerList = CCArray::create();
    
    XMLElement* towerListXMLElement = root->FirstChildElement(TAG_TOWER_LIST);
    
    for (XMLElement* element = towerListXMLElement->FirstChildElement(TAG_TOWER); element; element = element->NextSiblingElement())
    {
        towerList->addObject(XMLMapParser::getTowerStructDTOFromXMLNode(element));
    }
    
    return towerList;
}

CCArray* XMLMapParser::getSensorObjectDTOListFromXMLElement(XMLElement* root)
{
    CCArray* sensorList = CCArray::create();
    
    XMLElement* sensorListXMLElement = root->FirstChildElement(TAG_SENSOR_OBJECT_LIST);
    
    for (XMLElement* element = sensorListXMLElement->FirstChildElement(TAG_SENSOR_OBJECT); element; element = element->NextSiblingElement())
    {
        sensorList->addObject(XMLMapParser::getSensorObjectDTOFromXMLNode(element));
    }
    
    return sensorList;
}

CCArray* XMLMapParser::getWallDTOListFromXMLElement(XMLElement* root)
{
    CCArray* wallList = CCArray::create();
    
    XMLElement* sensorListXMLElement = root->FirstChildElement(TAG_WALL_LIST);
    
    for (XMLElement* element = sensorListXMLElement->FirstChildElement(TAG_WALL); element; element = element->NextSiblingElement())
    {
        wallList->addObject(XMLMapParser::getWallDTOFromXMLNode(element));
    }
    
    return wallList;
}

CCPoint XMLMapParser::getHeroRevivePositionFromXMLElement(XMLElement* root)
{
    CCPoint position;
    
    XMLElement* revivePosition = root->FirstChildElement(TAG_REVIVE_POSITION);
    
    if(revivePosition->FirstChildElement(TAG_POSITION) != NULL)
    {
        XMLElement* positionXMLElement = revivePosition->FirstChildElement(TAG_POSITION);
        
        position.x = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_X));
        position.y = atof(positionXMLElement->Attribute(ATTRIBUTE_POSITION_Y));
    }
    
    return position;
}
