//
//  MapSelectLayer.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "MapSelectLayer.h"

#include "XMLMapListParser.h"
#include "TestScene.h"

using cocos2d::gui::SEL_TouchEvent;
using cocos2d::gui::SEL_ListViewEvent;

MapSelectLayer::MapSelectLayer()
{
    
}

MapSelectLayer::~MapSelectLayer()
{

}

CCScene* MapSelectLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MapSelectLayer *layer = MapSelectLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MapSelectLayer* MapSelectLayer::layer()
{
    // 'layer' is an autorelease object
    MapSelectLayer *layer = MapSelectLayer::create();
    return layer;
}

bool MapSelectLayer::init()
{
    if(!cocos2d::gui::TouchGroup::init())
    {
        return false;
    }
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("MapSelectScene_1.ExportJson");
    
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
    
    loadAllUI(ul);
    this->addWidget(ul);
    

    return true;
}

void MapSelectLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    this->btnBack = (cocos2d::gui::Button*)ul->getChildByName("back_button");
    this->listMap = (cocos2d::gui::ListView*)ul->getChildByName("map_list");

    this->btnBack->addTouchEventListener(this, toucheventselector(MapSelectLayer::backButtonTouchEvent));
    
    this->listMap->setGravity(cocos2d::gui::LISTVIEW_GRAVITY_CENTER_VERTICAL);
    this->listMap->addEventListenerListView(this, listvieweventselector(MapSelectLayer::onSelectedListMap));
    //
    loadMapList();
}

void MapSelectLayer::backButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->popScene();
            break;
        default:
            break;
    }
}

void MapSelectLayer::listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
            CCString* mapId = (CCString*)this->listMap->getItem(this->listMap->getCurSelectedIndex())->getUserObject();
            if(mapId != NULL)
            {
                CCLOG("%s",mapId->getCString());

                CCScene* scene = TestScene::scene();
                CCDirector::sharedDirector()->pushScene(scene);
            }
            break;
        }
        default:
            break;
    }

}

void MapSelectLayer::loadMapList()
{
    std::vector<MapSelectData> listMap = XMLMapListParser::getMapList();
    for(int i=0 ; i<listMap.size() ; i++)
    {
        cocos2d::gui::Button* button = (cocos2d::gui::Button*)cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("MapListItem_1.ExportJson")->getChildByName("item")->clone();
        
        if(listMap[i].getstate() == true)
        {
            CCLOG("aa %s",listMap[i].getSelector().selectedTexture.c_str());

            button->loadTextures(listMap[i].getSelector().activeTexture.c_str(), listMap[i].getSelector().selectedTexture.c_str(), listMap[i].getSelector().activeTexture.c_str(),cocos2d::gui::UI_TEX_TYPE_PLIST);
            
            CCString* mapID = CCString::create(listMap[i].getID().data());
            button->setUserObject(mapID);
            button->addTouchEventListener(this, toucheventselector(MapSelectLayer::listItemTouchEvent));
        }
        else
        {
            button->loadTextures("map_lock_1.png","map_lock_1.png","map_lock_1.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        }
        this->listMap->pushBackCustomItem(button);
    }
}

void MapSelectLayer::onSelectedListMap(CCObject* sender, cocos2d::gui::ListViewEventType type)
{
//    CCLOG("%d",this->listMap->getCurSelectedIndex());
//    this->listMap->getItem(this->listMap->getCurSelectedIndex());
}