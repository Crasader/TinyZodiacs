//
//  HeroSelectScene.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#ifndef __TinyZodiacs__HeroSelectScene__
#define __TinyZodiacs__HeroSelectScene__

#include <iostream>
#include "cocos2d.h"
#include "HeroSelectLayer.h"

USING_NS_CC;

class HeroSelectScene: public CCLayer
{
private:
public:
    ~HeroSelectScene();
    virtual bool init();
    void initScene();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(HeroSelectScene);
};

#endif /* defined(__TinyZodiacs__HeroSelectScene__) */
