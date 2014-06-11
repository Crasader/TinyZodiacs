//
//  HeroSelectLayer.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#include "HeroSelectLayer.h"
using cocos2d::gui::SEL_TouchEvent;
using cocos2d::gui::SEL_ListViewEvent;
HeroSelectLayer::HeroSelectLayer()
{
    this->listHeroPreviewDTO = CCArray::create();
    this->listHeroPreviewDTO->retain();
}

HeroSelectLayer::~HeroSelectLayer()
{
    this->listHeroPreviewDTO->release();
}

bool HeroSelectLayer::init()
{
    if(!cocos2d::gui::TouchGroup::init())
    {
        return false;
    }
    
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("MapSelectScene_1.ExportJson");
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
    
    this->addWidget(ul);
    
    this->lvHeroPreview = (cocos2d::gui::ListView*)ul->getChildByName("map_list");
    this->btnBack = (cocos2d::gui::Button*)ul->getChildByName("back_button");
    this->btnBack->addTouchEventListener(this, toucheventselector(HeroSelectLayer::backButtonTouchEvent));
    
    lvHeroPreview->setGravity(cocos2d::gui::LISTVIEW_GRAVITY_CENTER_VERTICAL);
    lvHeroPreview->setItemsMargin(50);
    loadHeroPreviewList();
    return true;
}

void HeroSelectLayer::loadHeroPreviewList()
{
    CCArray* arr = HeroLoader::loadListHero("hero_list.xml");
    
    this->listHeroPreviewDTO->addObjectsFromArray(arr);
    
    CCObject* object = NULL;
    
    


    CCARRAY_FOREACH(this->listHeroPreviewDTO, object)
    {
        HeroPreviewDTO* heroPreviewDTO = static_cast<HeroPreviewDTO*>(object);
        
        
        ImageView* imageView = ImageView::create();
        imageView->loadTexture(CCString::createWithFormat("%s_idle_1.png",heroPreviewDTO->id.c_str())->getCString(), UI_TEX_TYPE_PLIST);
        imageView->setAnchorPoint(ccp(0.5f,0.5f));
        
        
        Layout* layout = Layout::create();
        layout->setSize(CCSize(400,200));
   
        
        imageView->setPosition(layout->getSize()/2);
        layout->addChild(imageView);
        layout->setUserData(heroPreviewDTO);
        
        layout->setTouchEnabled(true);
        layout->addTouchEventListener(this, toucheventselector(HeroSelectLayer::listItemTouchEvent));
        
        lvHeroPreview->pushBackCustomItem(layout);
    }
    
}

void HeroSelectLayer::backButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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


void HeroSelectLayer::listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            HeroPreviewDTO* heroPreviewDTO = static_cast<HeroPreviewDTO*>(this->lvHeroPreview->getItem(this->lvHeroPreview->getCurSelectedIndex())->getUserData());
            
            DataCollector::getInstance()->getMatchData()->heroIDSelected = heroPreviewDTO->id;
            
            CCScene* scene = TestScene::scene();
            CCDirector::sharedDirector()->pushScene(scene);
            
            break;
        }
        default:
            break;
    }
    
}

