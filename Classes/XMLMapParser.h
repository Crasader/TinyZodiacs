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
#include <string.h>

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
};

#endif /* defined(__TinyZodiacs__XMLMapParser__) */
