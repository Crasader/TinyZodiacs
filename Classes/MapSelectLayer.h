//
//  MapSelectLayer.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#ifndef __TinyZodiacs__MapSelectLayer__
#define __TinyZodiacs__MapSelectLayer__

#include <iostream>
#include "cocos2d.h"
#include "CocosGUI.h"

USING_NS_CC;
class MapSelectLayer: public cocos2d::gui::TouchGroup
{
private:
protected:
    void loadAllUI(cocos2d::gui::Widget* ul);
    void loadMapList();
public:
    cocos2d::gui::Button *btnBack;
    cocos2d::gui::ListView* listMap;
    
    MapSelectLayer();
    ~MapSelectLayer();
    
    bool init();
    
    void backButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    void listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type);
    
    void onSelectedListMap(CCObject* sender, cocos2d::gui::ListViewEventType type);
    
    CREATE_FUNC(MapSelectLayer);
};

#endif /* defined(__TinyZodiacs__MapSelectLayer__) */
