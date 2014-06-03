//
//  GameplayScene.cpp
//  HelloWorld
//
//  Created by Minh Nhut Vo on 5/26/14.
//
//

#include "GameplayLayer.h"

using cocos2d::gui::SEL_TouchEvent;

GameplayLayer::GameplayLayer()
{
    this->btnLeft = NULL;
    this->btnRight = NULL;
    this->btnJump = NULL;
    this->btnSkill0 = NULL;
    this->btnSkill1 = NULL;
    this->btnSkill2 = NULL;
    
}

GameplayLayer::~GameplayLayer()
{
    
}

CCScene* GameplayLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameplayLayer *layer = GameplayLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GameplayLayer* GameplayLayer::layer()
{
    // 'layer' is an autorelease object
    GameplayLayer *layer = GameplayLayer::create();
    return layer;
}

bool GameplayLayer::init()
{
    if(AbstractScene::init() == false)
    {
        return false;
    }
    
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("GameplayScene_1.ExportJson");
    
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
    
    loadAllUI(ul);
    
    this->addWidget(ul);
    return true;
}

void GameplayLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    //Getbutton
    cocos2d::gui::Button *BtnLeft,*BtnRight,*BtnJump,*BtnSkill0,*BtnSkill1,*BtnSkill2;
    
    BtnLeft  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("left_btn");
    BtnRight  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("right_btn");
    BtnJump  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("jump_button");
    BtnSkill0  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("skill_0_button");
    BtnSkill1  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("skill_1_button");
    BtnSkill2  = (cocos2d::gui::Button*)ul->getChildByName("controller_layer")->getChildByName("skill_2_button");
    
    this->btnLeft = HoldableUIButton::create();;
    this->btnRight = HoldableUIButton::create();;
    this->btnJump = HoldableUIButton::create();;
    this->btnSkill0 = HoldableUIButton::create();;
    this->btnSkill1 = HoldableUIButton::create();;
    this->btnSkill2 = HoldableUIButton::create();;
    
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnLeft, BtnLeft);
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnRight, BtnRight);
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnJump, BtnJump);
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnSkill0, BtnSkill0);
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnSkill1, BtnSkill1);
    cloneAndRemoveButton(ul->getChildByName("controller_layer"), this->btnSkill2, BtnSkill2);
    
    this->listAssignedWidget->addObject(this->btnLeft);
    this->listAssignedWidget->addObject(this->btnRight);
    
    //Get label and process
    processMonsterLeft  = (cocos2d::gui::LoadingBar*)ul->getChildByName("infomation_layer")->getChildByName("monster_left_process");
    lblWave  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("infomation_layer")->getChildByName("wave_label");
    lblTimeLeft  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("infomation_layer")->getChildByName("time_left_label");
    lblMoney  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("infomation_layer")->getChildByName("money_number_label");
    listWave  = (cocos2d::gui::ListView*)ul->getChildByName("infomation_layer")->getChildByName("wave_list");
    
    //add touch event
    this->btnLeft->addTouchEventListener(this, toucheventselector(GameplayLayer::leftButtonTouchEvent));
    this->btnRight->addTouchEventListener(this, toucheventselector(GameplayLayer::rightButtonTouchEvent));
    this->btnJump->addTouchEventListener(this, toucheventselector(GameplayLayer::jumpButtonTouchEvent));
    this->btnSkill0->addTouchEventListener(this, toucheventselector(GameplayLayer::skill0ButtonTouchEvent));
    this->btnSkill1->addTouchEventListener(this, toucheventselector(GameplayLayer::skill1ButtonTouchEvent));
    //    this->btnSkill2->addTouchEventListener(this, toucheventselector(GameplayLayer::skill2ButtonTouchEvent));
    
}

void GameplayLayer::cloneAndRemoveButton(cocos2d::gui::Widget* ul, HoldableUIButton* mButton,cocos2d::gui::Button* button)
{
    mButton->copy(button);
    
    ul->removeChild(button);
    ul->addChild(mButton);
}

void GameplayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    AbstractScene::ccTouchMoved(pTouch, pEvent);
}

void GameplayLayer::setGoldValue(int number)
{
    this->lblMoney->setText(CCString::createWithFormat("%d",number)->getCString());
}

void GameplayLayer::setTimeValue(int number)
{
    this->lblTimeLeft->setText(CCString::createWithFormat("%d",number)->getCString());
}

void GameplayLayer::setWaveValue(int number)
{
    this->lblWave->setText(CCString::createWithFormat("Wave %d",number)->getCString());
}

void GameplayLayer::setMonsterProcessValue(int maxMonsterQuantity, int currentMonsterQuantity)
{
    this->processMonsterLeft->setPercent(((1.0f*currentMonsterQuantity/maxMonsterQuantity))*100);
}

bool GameplayLayer::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    switch (commandID)
    {
        case DISPLAY_NEW_WAVE:
        {
            int* waveNumber = static_cast<int*>(data);
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            CCLabelTTF* labelStyle = CCLabelTTF::create("", "Marker Felt", 150);
            labelStyle->setOpacity(100);
            
            TextShowEffect* effect = TextShowEffect::create();
            effect->setContent(CCString::createWithFormat("Wave %d", *waveNumber)->getCString());
            effect->setLabelStyle(labelStyle);
            
            EffectManager::getInstance()->runEffect(effect, ccp(size.width/2, size.height/2),this);
            
            setWaveValue(*waveNumber);
            delete waveNumber;
        }
            break;
        case DISPLAY_RESULT:
        {
            int* waveNumber = static_cast<int*>(data);
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            CCLabelTTF* labelStyle = CCLabelTTF::create("", "Marker Felt", 150);
            labelStyle->setOpacity(100);
            
            TextShowEffect* effect = TextShowEffect::create();
            if(waveNumber == 0)
            {
                effect->setContent("LOSE");
            }
            else
            {
                effect->setContent("WIN");
            }
            
            effect->setLabelStyle(labelStyle);
            
            EffectManager::getInstance()->runEffect(effect, ccp(size.width/2, size.height/2),this);
            
            setWaveValue(*waveNumber);
            delete waveNumber;
        }
            break;

        case DISPLAY_WORLD_COORDINATE:
        {
            CCPoint* point = static_cast<CCPoint*>(data);
            this->lblTimeLeft->setText(CCString::createWithFormat("%0.1f - %0.1f",point->x,point->y)->getCString());
        }
            break;
        case DISPLAY_MONSTER_COUNT:
        {
            vector<int>* arr = static_cast<vector<int>*>(data);
//            CCLOG("%d-%d",arr->at(1),arr->at(1)-arr->at(0));
            setMonsterProcessValue(arr->at(1),arr->at(1)-arr->at(0));
        }
            break;
        case CHANGE_SKILL_0_TEXTURE_SET:
        {
            TextureSelector* selector = (TextureSelector*)data;
            this->btnSkill0->loadTextures(selector->activeTexture.c_str(), selector->selectedTexture.c_str(), selector->deactiveTexture.c_str(),cocos2d::gui::UI_TEX_TYPE_PLIST);
            delete selector;
        }
            break;
        case CHANGE_SKILL_1_TEXTURE_SET:
        {
            TextureSelector* selector = (TextureSelector*)data;
            this->btnSkill1->loadTextures(selector->activeTexture.c_str(), selector->selectedTexture.c_str(), selector->deactiveTexture.c_str(),cocos2d::gui::UI_TEX_TYPE_PLIST);
            delete selector;
        }
            break;
        case CHANGE_SKILL_2_TEXTURE_SET:
        {
            TextureSelector* selector = (TextureSelector*)data;
            this->btnSkill2->loadTextures(selector->activeTexture.c_str(), selector->selectedTexture.c_str(), selector->deactiveTexture.c_str(),cocos2d::gui::UI_TEX_TYPE_PLIST);
            delete selector;
        }
            break;
        case CHANGE_STATE:
        {
            StateCommandData* mData = (StateCommandData*)data;
            if(data != NULL)
            {
                switch (mData->controllerId) {
                    case SKILL_0_BTN:
                        this->btnSkill0->setActive(mData->isActive);
                        break;
                    case SKILL_1_BTN:
                        this->btnSkill1->setActive(mData->isActive);
                        break;
                    case SKILL_2_BTN:
                        this->btnSkill2->setActive(mData->isActive);
                        break;
                    default:
                        break;
                }
            }
            delete mData;
        }
            break;
        case INVISIBLE_ALL_HERO_CONTROLLER:
        {
            this->btnLeft->setVisible(false);
            this->btnRight->setVisible(false);
            this->btnJump->setVisible(false);
            this->btnSkill0->setVisible(false);
            this->btnSkill1->setVisible(false);
             this->btnSkill2->setVisible(false);
    
        }
            break;
        case VISIBLE_ALL_HERO_CONTROLLER:
        {
            this->btnLeft->setVisible(true);
            this->btnRight->setVisible(true);
            this->btnJump->setVisible(true);
            this->btnSkill0->setVisible(true);
            this->btnSkill1->setVisible(true);
            this->btnSkill2->setVisible(true);

        }
            break;
            
        default:
            break;
    }
    return true;
}

bool GameplayLayer::removeSubController(Controller* controller)
{
    Controller::removeSubController(controller);
    return true;
}

void GameplayLayer::leftButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_LEFT);
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_LEFT);
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_LEFT);
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            break;
        default:
            break;
    }
}

void GameplayLayer::rightButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            break;
        default:
            break;
    }
}

void GameplayLayer::jumpButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_JUMP);
            break;
            //        case cocos2d::gui::TOUCH_EVENT_MOVED:
            //            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_HOLD:
            //            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_RIGHT);
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            //            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_ENDED:
            //            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_MOVE_STOP);
            //            break;
        default:
            break;
    }
}

void GameplayLayer::skill0ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_1);
            break;
            //        case cocos2d::gui::TOUCH_EVENT_MOVED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_HOLD:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_ENDED:
            //
            //            break;
        default:
            break;
    }
}

void GameplayLayer::skill1ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_2);
            break;
            //        case cocos2d::gui::TOUCH_EVENT_MOVED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_HOLD:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_ENDED:
            //
            //            break;
        default:
            break;
    }
}

void GameplayLayer::skill2ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_1);
            break;
            //        case cocos2d::gui::TOUCH_EVENT_MOVED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_HOLD:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            //
            //            break;
            //        case cocos2d::gui::TOUCH_EVENT_ENDED:
            //
            //            break;
        default:
            break;
    }
}