//
//  MapCreator.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 2/18/14.
//
//

#ifndef __SampleCocosProject__MapCreator__
#define __SampleCocosProject__MapCreator__

#include <iostream>
#include "Map.h"
#include "GameWorld.h"
#include "MapObjectDTO.h"
#include "MapDTO.h"
#include "Map.h"
#include "ObjectFactory.h"
#include "MapFactory.h"
#include "MapParallaxBackground.h"
#include "BackgroundDTO.h"



class MapCreator
{
private:
protected:
public:
    
    MapCreator();
    virtual ~MapCreator();
    
    Map* createMap(const char *id, GameWorld* gameWorld);
    Map* createMap(MapDTO* mapDTO, GameWorld* gameWorld);
    MapParallaxBackground* createParallaxBackground(CCArray* listBackgroundDTO, float width, float height);

    MapParallaxForeground* createParallaxForeground(CCArray* listForegroundDTO, float width, float height);
    
};


#endif /* defined(__SampleCocosProject__MapCreator__) */
