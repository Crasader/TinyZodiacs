//
//  MapSelectScene.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#ifndef __TinyZodiacs__MapSelectScene__
#define __TinyZodiacs__MapSelectScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MapSelectScene: public cocos2d::CCLayer
{
private:
public:
    ~MapSelectScene();
    virtual bool init();
    void initScene();
    
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MapSelectScene);
    
};
#endif /* defined(__TinyZodiacs__MapSelectScene__) */
