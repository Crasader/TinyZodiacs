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

class MapCreator
{
private:
protected:
public:
    
    MapCreator();
    virtual ~MapCreator();
    
    Map* createMap(const char *id);
    
   
    
    
};


#endif /* defined(__SampleCocosProject__MapCreator__) */
