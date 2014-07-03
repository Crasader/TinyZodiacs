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
    lvHeroPreview->setBounceEnabled(true);
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
        
        
        Button* button = Button::create();
        
        button->ignoreContentAdaptWithSize(false);
        button->setSizeType(SIZE_PERCENT);
        button->setSizePercent(ccp(1,1));
        TextureSelector textureSelector = XMLButtonSelectorParser::parseData(heroPreviewDTO->buttonID);
        button->loadTextures(textureSelector.activeTexture.c_str(), textureSelector.selectedTexture.c_str(), textureSelector.deactiveTexture.c_str(), cocos2d::gui::UI_TEX_TYPE_PLIST);
        
        
        Layout* layout = Layout::create();
        layout->setSize(CCSize(200,200));
   
        
        button->setPosition(layout->getSize()/2);;
        button->setTouchEnabled(true);
        button->addTouchEventListener(this, toucheventselector(HeroSelectLayer::listItemTouchEvent));
        
        layout->addChild(button, 0, 1);
        layout->setUserData(heroPreviewDTO);

        
        lvHeroPreview->pushBackCustomItem(layout);
        
        ///
       
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
            
            CCScene* scene = LoadingScene::scene();
            CCDirector::sharedDirector()->pushScene(scene);
            
            break;
        }
        default:
            break;
    }
    
}

