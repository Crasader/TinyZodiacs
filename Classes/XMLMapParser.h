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
#include "WallDTO.h"

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
    static WallDTO* getWallDTOFromXMLNode(XMLElement* wallXMLElement);

    
    static CCArray* getMonsterFactoryDTOListFromXMLElement(XMLElement* root);
    static CCArray* getItemCreatorDTOListFromXMLElement(XMLElement* root);
    static CCArray* getWaveDTOListFromXMLElement(XMLElement* root);
    static CCArray* getTowerStructDTOListFromXMLElement(XMLElement* root);
    static CCArray* getSensorObjectDTOListFromXMLElement(XMLElement* root);
    static CCArray* getWallDTOListFromXMLElement(XMLElement* root);
    static CCPoint getHeroRevivePositionFromXMLElement(XMLElement* root);
    
};

#endif /* defined(__TinyZodiacs__XMLMapParser__) */
