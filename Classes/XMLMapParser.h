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

#define BACKGROUND_LIST "background_list"
#define BACKGROUND "background"
#define BACKGROUND_IMAGE_NAME "image_name"
#define BACKGROUND_SPRITESHEET_NAME "spritesheet_name"

#define RATIO "ratio"
#define RATIO_X "x"
#define RATIO_Y "y"
#define LAYER_INDEX "layer_index"
#define POSITION "position"
#define POSITION_X "x"
#define POSITION_Y "y"


#define FOREGROUND_LIST "foreground_list"
#define FOREGROUND "foreground"
#define FOREGROUND_IMAGE_NAME "image_name"

#define MAP_ID "id"
#define MAP_WIDTH "width"
#define MAP_HEIGHT "height"

#define MAP_OBJECT_LIST "map_object_list"
#define MAP_OBJECT "map_object"
#define MAP_OBJECT_ID "id"
#define MAP_OBJECT_IMAGE_NAME "image_name"
#define MAP_OBJECT_BODY_NAME "body_name"




USING_NS_CC;
using namespace tinyxml2;

class XMLMapParser
{
public:
    static MapObjectDTO* getMapObjectDTOFromXMLNode(XMLElement* mapObjectXMLElement);
    static MapDTO* getMapDTOFromXMLNode(XMLElement* mapXMLElement);
    static BackgroundDTO* getBackgroundDTOFromXMLNode(XMLElement* backgroundXMLElement);
    static ForegroundDTO* getForegroundDTOFromXMLNode(XMLElement* foregroundXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLMapParser__) */
