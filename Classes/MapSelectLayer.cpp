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
#include "HeroSelectScene.h"
#include "AnimationEffect.h"
#include "EffectManager.h"

using cocos2d::gui::SEL_TouchEvent;
using cocos2d::gui::SEL_ListViewEvent;

MapSelectLayer::MapSelectLayer()
{
    
}

MapSelectLayer::~MapSelectLayer()
{

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
    this->listMap->setBounceEnabled(true);
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
            
            CCLOG("sadasd %d", this->getParent()->retainCount());
            CCDirector::sharedDirector()->popToSceneStackLevel(1);
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
         
                DataCollector::getInstance()->getMatchData()->mapIDSelected = mapId->getCString();
                
                MapDTO* mapDTO = DataCollector::getInstance()->getMapDTOByKey(mapId->getCString());
                DataCollector::getInstance()->getMatchData()->resourcePackList.push_back(mapDTO->resourcePack);
                
                CCScene* heroSelectScene = HeroSelectScene::scene();
                CCDirector::sharedDirector()->pushScene(heroSelectScene);
            }
            break;
        }
        default:
            break;
    }

}

void MapSelectLayer::loadMapList()
{
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
    std::vector<MapSelectData> listMap = XMLMapListParser::getMapList();
    for(int i=0 ; i<listMap.size() ; i++)
    {
        
        cocos2d::gui::Button* button = (cocos2d::gui::Button*)cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("MapListItem_1.ExportJson")->getChildByName("item")->clone();
        
        if(listMap[i].getstate() == true)
        {
            TextureSelector textureSelector = XMLButtonSelectorParser::parseData(listMap[i].buttonID);
    
            button->loadTextures(textureSelector.activeTexture.c_str(), textureSelector.selectedTexture.c_str(), textureSelector.deactiveTexture.c_str(), cocos2d::gui::UI_TEX_TYPE_PLIST);
            
            
            CCString* mapID = CCString::create(listMap[i].getID().data());
            button->setUserObject(mapID);
            button->addTouchEventListener(this, toucheventselector(MapSelectLayer::listItemTouchEvent));
        }
        else
        {
            button->loadTextures("map_lock.png","map_lock.png","map_lock.png",cocos2d::gui::UI_TEX_TYPE_PLIST);
        }
        this->listMap->pushBackCustomItem(button);
    }
}

void MapSelectLayer::onSelectedListMap(CCObject* sender, cocos2d::gui::ListViewEventType type)
{
//    CCLOG("%d",this->listMap->getCurSelectedIndex());
//    this->listMap->getItem(this->listMap->getCurSelectedIndex());
}