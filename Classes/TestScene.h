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

class TestScene: public cocos2d::CCLayer
{
private:
    void menuBackCallBack(CCObject* pSender);
public:
    ~TestScene();
    virtual bool init();
    void initScene();
    
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(TestScene);
    
};

#endif /* defined(__SampleCocosProject__TestScene__) */
