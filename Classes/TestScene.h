//
//  TestScene.h
//  SampleCocosProject
//
//  Created by HoaPhat on 1/4/14.
//
//

#ifndef __SampleCocosProject__TestScene__
#define __SampleCocosProject__TestScene__

#include <iostream>
#include <cocos2d.h>
#include "ResourceLoader.h"
#include "ResourcePack.h"

class TestScene: public cocos2d::CCLayer
{
private:
    ResourcePack* resourcePack;
public:
    ~TestScene();
    virtual bool init();
    
    void initScene();
    
    static cocos2d::CCScene* scene();
    
    void loadResource();
    
    CREATE_FUNC(TestScene);
    
};

#endif /* defined(__SampleCocosProject__TestScene__) */
