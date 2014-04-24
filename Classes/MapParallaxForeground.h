//
//  MapParallaxForeground.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#ifndef __TinyZodiacs__MapParallaxForeground__
#define __TinyZodiacs__MapParallaxForeground__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MapParallaxForeground: public CCParallaxNode
{
private:
protected:
public:
    MapParallaxForeground();
    virtual ~MapParallaxForeground();
    
    virtual bool init();
    void addForeground(std::string imageName, std::string spritesheetName, float ratio_x, float ratio_y, float layerIndex, float positionX, float positionY);
    
    CREATE_FUNC(MapParallaxForeground);
};

#endif /* defined(__TinyZodiacs__MapParallaxForeground__) */
