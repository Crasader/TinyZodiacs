//
//  TowerDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/26/14.
//
//

#ifndef __TinyZodiacs__TowerDTO__
#define __TinyZodiacs__TowerDTO__

#include <iostream>

#include "cocos2d.h"
#include "GameObject.h"
#include "CharacterDTO.h"

using namespace std;
USING_NS_CC;

class TowerDTO: public CharacterDTO
{
public:
    std::string towerSensorId;
    
    TowerDTO();
    virtual ~TowerDTO();
    
    virtual bool init();
    CREATE_FUNC(TowerDTO);
};

class TowerStructDTO: public CCObject
{
private:
protected:
public:
    TowerStructDTO();
    virtual ~TowerStructDTO();
    
    virtual bool init();

    string id;
    Group group;
    float positionX;
    float positionY;
    
    CREATE_FUNC(TowerStructDTO);
};


#endif /* defined(__TinyZodiacs__TowerDTO__) */
