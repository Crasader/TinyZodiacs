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

#define BACKGROUND_LIST "background_list"
#define BACKGROUND "background"
#define BACKGROUND_IMAGE_NAME "image_name"
#define BACKGROUND_SPRITESHEET_NAME "spritesheet_name"
#define BACKGROUND_RATIO_X "ratio_x"
#define BACKGROUND_RATIO_Y "ratio_y"
#define BACKGROUND_ORDER_INDEX "order"

#define MAP_ID "id"
#define MAP_WIDTH "width"
#define MAP_HEIGHT "height"

#define MAP_OBJECT_LIST "map_object_list"
#define MAP_OBJECT "map_object"
#define MAP_OBJECT_ID "id"
#define MAP_OBJECT_IMAGE_NAME "image_name"
#define MAP_OBJECT_BODY_NAME "body_name"
#define MAP_OBJECT_POSITION "position"
#define MAP_OBJECT_POSITION_X "x"
#define MAP_OBJECT_POSITION_Y "y"


USING_NS_CC;
using namespace tinyxml2;

class XMLMapParser
{
public:
    static MapObjectDTO* getMapObjectDTOFromXMLNode(XMLElement*mapObjectXMLElement);
    static MapDTO* getMapDTOFromXMLNode(XMLElement *mapXMLElement);
    static BackgroundDTO* getBackgroundDTOFromXMLNode(XMLElement*backgroundXMLElement);
};

#endif /* defined(__TinyZodiacs__XMLMapParser__) */
