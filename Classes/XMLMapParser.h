//
//  XMLMapParser.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/18/14.
//
//

#ifndef __TinyZodiacs__XMLMapParser__
#define __TinyZodiacs__XMLMapParser__

#include <iostream>
#include "MapObjectDTO.h"
#include "MapDTO.h"
#include "BackgroundDTO.h"
#include "ForegroundDTO.h"
#include "SensorObjectDTO.h"
#include "TowerDTO.h"
#include "MonsterCreatorDTO.h"
#include "MonsterFactoryDTO.h"
#include "Util.h"
#include <string.h>
#include "ItemCreatorDTO.h"
#include "XMLHelper.h"
#include "XMLItemParser.h"
#include "WaveDTO.h"

#define TAG_BACKGROUND_LIST "background_list"
#define TAG_BACKGROUND "background"
#define ATTRIBUTE_BACKGROUND_IMAGE_NAME "image_name"
#define ATTRIBUTE_BACKGROUND_SPRITESHEET_NAME "spritesheet_name"

#define TAG_RATIO "ratio"
#define ATTRIBUTE_RATIO_X "x"
#define ATTRIBUTE_RATIO_Y "y"
#define ATTRIBUTE_LAYER_INDEX "layer_index"
#define TAG_POSITION "position"
#define ATTRIBUTE_POSITION_X "x"
#define ATTRIBUTE_POSITION_Y "y"


#define TAG_FOREGROUND_LIST "foreground_list"
#define TAG_FOREGROUND "foreground"
#define ATTRIBUTE_FOREGROUND_IMAGE_NAME "image_name"

#define ATTRIBUTE_MAP_ID "id"
#define ATTRIBUTE_MAP_WIDTH "width"
#define ATTRIBUTE_MAP_HEIGHT "height"

#define TAG_MAP_OBJECT_LIST "map_object_list"
#define TAG_MAP_OBJECT "map_object"
#define ATTRIBUTE_MAP_OBJECT_ID "id"
#define ATTRIBUTE_MAP_OBJECT_IMAGE_NAME "image_name"
#define ATTRIBUTE_MAP_OBJECT_BODY_NAME "body_name"

#define TAG_CAN_PASS "can_pass"

//sensor
#define TAG_SENSOR_OBJECT_LIST "sensor_object_list"
#define TAG_SENSOR_OBJECT "sensor_object"
#define ATTRIBUTE_SENSOR_OBJECT_MUSTSTOP "must_stop"
#define ATTRIBUTE_SENSOR_OBJECT_ISBACK "is_back"
#define ATTRIBUTE_SENSOR_OBJECT_DIRECTION "direction"
#define ATTRIBUTE_SENSOR_OBJECT_MOVE_SPEED "move_speed"
#define ATTRIBUTE_SENSOR_OBJECT_JUMP_HEIGHT "jump_height"
#define TAG_EDGE "edge"
#define ATTRIBUTE_EDGE_X "x"
#define ATTRIBUTE_EDGE_Y "y"
#define TAG_LANE "lane"

//tower
#define TAG_TOWER_LIST "tower_list"
#define TAG_TOWER "tower"
#define ATTRIBUTE_TOWER_ID "id"
#define ATTRIBUTE_TOWER_GROUP "group"

//monster factory
#define TAG_MONSTER_FACTORY_LIST "monster_factory_list"
#define TAG_MONSTER_FACTORY "monster_factory"
#define ATTRIBUTE_MONSTER_FACTORY_GROUP "group"
#define ATTRIBUTE_MONSTER_FACTORY_MAX "max"
#define TAG_MONSTER_CREATOR "monster_creator"
#define ATTRIBUTE_MONSTER_CREATOR_DELAY_PER_UNIT "delay_per_unit"
#define ATTRIBUTE_MONSTER_CREATOR_DELAY "delay"
#define ATTRIBUTE_MONSTER_CREATOR_LANE "lane"
#define TAG_MONSTER_LIST "monster_list"
#define TAG_MONSTER "monster"
#define ATTRIBUTE_MONSTER_ID "id"
#define ATTRIBUTE_MONSTER_QUANTITY "quantity"

//item creator
#define TAG_ITEM_CREATOR_LIST "item_creator_list"
#define TAG_ITEM_CREATOR "item_creator"
#define ATTRIBUTE_ITEM_CREATOR_MAX "max"
#define ATTRIBUTE_ITEM_CREATOR_DELAY_MIN "delay_min"
#define ATTRIBUTE_ITEM_CREATOR_DELAY_MAX "delay_max"
#define TAG_ITEM_CREATOR_BEGIN_POSITION "begin_position"
#define TAG_ITEM_CREATOR_END_POSITION "end_position"

//wave
#define TAG_WAVE_LIST "wave_list"
#define TAG_WAVE "wave"


USING_NS_CC;
using namespace tinyxml2;

class XMLMapParser
{
public:
    static MapObjectDTO* getMapObjectDTOFromXMLNode(XMLElement* mapObjectXMLElement);
    static MapDTO* getMapDTOFromXMLNode(XMLElement* mapXMLElement);
    static BackgroundDTO* getBackgroundDTOFromXMLNode(XMLElement* backgroundXMLElement);
    static ForegroundDTO* getForegroundDTOFromXMLNode(XMLElement* foregroundXMLElement);
    static SensorObjectDTO* getSensorObjectDTOFromXMLNode(XMLElement* sensorObjectXMLElement);
    static TowerStructDTO* getTowerStructDTOFromXMLNode(XMLElement* towerXMLElement);
    static MonsterCreatorDTO* getMonsterCreatorDTOFromXMLNode(XMLElement* monsterCreatorXMLElement);
    static MonsterFactoryDTO* getMonsterFactoryDTOFromXMLNode(XMLElement* monsterFactoryXMLElement);
    static ItemCreatorDTO* getItemCreatorDTOFromXMLNode(XMLElement* itemCreatorXMLElement);
    static WaveDTO* getWaveFromXMLNode(XMLElement* waveXMLElement);
    
    static CCArray* getMonsterFactoryDTOListFromXMLElement(XMLElement* root);
    static CCArray* getItemCreatorDTOListFromXMLElement(XMLElement* root);
    static CCArray* getWaveDTOListFromXMLElement(XMLElement* root);
    static CCArray* getTowerStructDTOListFromXMLElement(XMLElement* root);
    static CCArray* getSensorObjectDTOListFromXMLElement(XMLElement* root);

};

#endif /* defined(__TinyZodiacs__XMLMapParser__) */
