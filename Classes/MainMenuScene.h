//
//  MainMenuScene.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/5/14.
//
//

#ifndef __TinyZodiacs__MainMenuScene__
#define __TinyZodiacs__MainMenuScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene: public cocos2d::CCLayer
{
private:
    void menuBackCallBack(CCObject* pSender);
public:
    ~MainMenuScene();
    virtual bool init();
    void initScene();
    
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MainMenuScene);
    
};

#endif /* defined(__TinyZodiacs__MainMenuScene__) */
