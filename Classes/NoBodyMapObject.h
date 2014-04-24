//
//  NoBodyMapObject.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/25/14.
//
//

#ifndef __TinyZodiacs__NoBodyMapObject__
#define __TinyZodiacs__NoBodyMapObject__

#include <iostream>
#include "cocos2d.h"
#include "MapObject.h"

USING_NS_CC;

class NoBodyMapObject: public MapObject
{
private:
protected:
public:
    NoBodyMapObject();
    ~NoBodyMapObject();
    
    virtual void update(float dt);
    
    virtual void setPositionInPixel(const cocos2d::CCPoint& pos);
    virtual cocos2d::CCPoint getPositionInPixel();
    
    CREATE_FUNC(NoBodyMapObject);
};


#endif /* defined(__TinyZodiacs__NoBodyMapObject__) */
