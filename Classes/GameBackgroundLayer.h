//
//  GameBackgroundLayer.h
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 1/7/14.
//
//

#ifndef __SampleCocosProject__GameBackgroundLayer__
#define __SampleCocosProject__GameBackgroundLayer__

#include <iostream>
#include "cocos2d.h"

class GameBackgroundLayer: public cocos2d::CCLayer
{
public:
    GameBackgroundLayer();
    virtual ~GameBackgroundLayer();
    virtual bool init();
    
    CREATE_FUNC(GameBackgroundLayer);
    void scrollBackground(cocos2d::CCObject *pSender);
    
private:
    cocos2d::CCParallaxNode* parallaxBackgroundNode;
};
#endif /* defined(__SampleCocosProject__GameBackgroundLayer__) */
