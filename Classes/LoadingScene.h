//
//  LoadingScene.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/11/14.
//
//

#ifndef __TinyZodiacs__LoadingScene__
#define __TinyZodiacs__LoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "HeroSelectLayer.h"

USING_NS_CC;

class LoadingScene: public CCLayer
{
private:
public:
    int currResourceCount;
    int resourceCount;
    ~LoadingScene();
    virtual bool init();
    void initScene();
    
    static cocos2d::CCScene* scene();
    
    void loadResource();
    void loadImage(const char* imageFilename, const char* plistFilename, CCTexture2DPixelFormat texturePixelFormat = kTexture2DPixelFormat_Default);
    void finishLoadingResource(CCObject* object);
    
    CREATE_FUNC(LoadingScene);
};

#endif /* defined(__TinyZodiacs__LoadingScene__) */
