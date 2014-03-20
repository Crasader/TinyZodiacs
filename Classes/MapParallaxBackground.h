//
//  MapParallaxBackground.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/19/14.
//
//

#ifndef __TinyZodiacs__MapParallaxBackground__
#define __TinyZodiacs__MapParallaxBackground__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MapParallaxBackground: public CCParallaxNode
{
private:
protected:
public:
    MapParallaxBackground();
    virtual ~MapParallaxBackground();
    
    virtual bool init();
    void addBackground(std::string imageName, std::string spritesheetName, float ratio_x, float ratio_y, float orderIndex, float width, float height);
    
    CREATE_FUNC(MapParallaxBackground);
};

#endif /* defined(__TinyZodiacs__MapParallaxBackground__) */
