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
#include "ResourcePack.h"

USING_NS_CC;

class HeroSelectScene: public CCLayer
{
private:
    ResourcePack* resourcePack;
public:
    ~HeroSelectScene();
    virtual bool init();
    
    void initScene();
    void loadResource();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(HeroSelectScene);
};

#endif /* defined(__TinyZodiacs__HeroSelectScene__) */
