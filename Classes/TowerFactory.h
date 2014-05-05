//
//  TowerFactory.h
//  TinyZodiacs
//
//  Created by NhutVM on 4/22/14.
//
//

#ifndef __TinyZodiacs__TowerFactory__
#define __TinyZodiacs__TowerFactory__

#include <iostream>
#include "CharacterFactory.h"
#include "cocos2d.h"
#include "Box2d/Box2D.h"
#include "CharacterDTO.h"
#include "Tower.h"
#include "GB2ShapeCache-x.h"
#include "DataCollector.h"
#include "SkillFactory.h"
#include "TowerDTO.h"

USING_NS_CC;

class TowerFactory: protected CharacterFactory
{
private:
protected:
    static void loadBody(CharacterDTO heroDTOData, Character* character, b2World* world);
    static Tower* createTower(CharacterDTO heroDTOData, b2World* world, bool isLocal);
public:
    static Tower* createTower(string ID,b2World* world);
    static Tower* createTower(TowerDTO* towerDTO ,b2World* world);

};


#endif /* defined(__TinyZodiacs__TowerFactory__) */
