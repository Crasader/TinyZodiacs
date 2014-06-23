//
//  HeroSelectLayer.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#ifndef __TinyZodiacs__HeroSelectLayer__
#define __TinyZodiacs__HeroSelectLayer__

#include <iostream>
#include "cocos2d.h"
#include "HeroLoader.h"
#include "DataCollector.h"
#include "TestScene.h"
#include "LoadingScene.h"
#include "XMLButtonSelectorParser.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::gui;

class HeroSelectLayer: public TouchGroup
{
private:
    CCArray* listHeroPreviewDTO;
    ListView* lvHeroPreview;
    Button* btnBack;
protected:
public:
    HeroSelectLayer();
    ~HeroSelectLayer();
    
    bool init();
    
    void loadHeroPreviewList();
    
    void backButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    CREATE_FUNC(HeroSelectLayer);
};

#endif /* defined(__TinyZodiacs__HeroSelectLayer__) */
