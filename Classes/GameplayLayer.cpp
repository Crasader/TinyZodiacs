//
//  GameplayScene.cpp
//  HelloWorld
//
//  Created by Minh Nhut Vo on 5/26/14.
//
//

#include "GameplayLayer.h"
#include "PauseLayer.h"

using cocos2d::gui::SEL_TouchEvent;
using namespace cocos2d::gui;

GameplayLayer::GameplayLayer()
{
    this->btnLeft = NULL;
    this->btnRight = NULL;
    this->btnJump = NULL;
    this->btnSkill0 = NULL;
    this->btnSkill1 = NULL;
    this->btnSkill2 = NULL;
    
    this->defenseList = CCArray::create();
    this->defenseList->retain();
    this->mainLayout = NULL;
}

GameplayLayer::~GameplayLayer()
{
    this->defenseList->release();
    ControllerManager::getInstance()->unregisterController(HERO_CONTROLLER, this);
}



bool GameplayLayer::init()
{
    if(AbstractScene::init() == false)
    {
        return false;
    }
    
    ControllerManager::getInstance()->registerController(HERO_CONTROLLER, this);
    
    cocos2d::gui::Widget* ul =cocos2d::gui::Widget::create();
    ul = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile("ControllerLayer_1.ExportJson");
    
    ul->setScale(CCDirector::sharedDirector()->getWinSize().width/ul->getSize().width, CCDirector::sharedDirector()->getWinSize().height/ul->getSize().height);
    
    this->mainLayout = ul;
    this->addWidget(ul);
    
    
    loadAllUI(ul);
    loadDefenseList();
    
    initUI();
    return true;
}

void GameplayLayer::loadAllUI(cocos2d::gui::Widget* ul)
{
    
    
    this->defenseListGroup = (Layout*)ul->getChildByName("defense_list_group");
    this->actionControlPanel = (Layout*)ul->getChildByName("controller_layer")->getChildByName("action_control_panel");
    this->movingControlPanel = (Layout*)ul->getChildByName("controller_layer")->getChildByName("movement_control_panel");
    
    //Getbutton
    cocos2d::gui::Button *BtnLeft,*BtnRight,*BtnJump,*BtnSkill0,*BtnSkill1,*BtnSkill2;
    
    BtnLeft  = (cocos2d::gui::Button*)this->movingControlPanel->getChildByName("left_button");
    BtnRight  = (cocos2d::gui::Button*)this->movingControlPanel->getChildByName("right_button");
    BtnJump  = (cocos2d::gui::Button*)this->actionControlPanel->getChildByName("jump_button");
    BtnSkill0  = (cocos2d::gui::Button*)this->actionControlPanel->getChildByName("skill_0_button");
    BtnSkill1  = (cocos2d::gui::Button*)this->actionControlPanel->getChildByName("skill_1_button");
    BtnSkill2  = (cocos2d::gui::Button*)this->actionControlPanel->getChildByName("skill_2_button");
    
    this->btnLeft = HoldableButton::create();
    this->btnRight = HoldableButton::create();
    this->btnJump = HoldableButton::create();
    this->btnSkill0 = HoldableButton::create();
    this->btnSkill1 = HoldableButton::create();
    this->btnSkill2 = HoldableButton::create();
    
    cloneAndRemoveButton(ul->getChildByName("controller_layer")->getChildByName("movement_control_panel"), this->btnLeft, BtnLeft);
    cloneAndRemoveButton(ul->getChildByName("controller_layer")->getChildByName("movement_control_panel"), this->btnRight, BtnRight);
    cloneAndRemoveButton(actionControlPanel, this->btnJump, BtnJump);
    cloneAndRemoveButton(actionControlPanel, this->btnSkill0, BtnSkill0);
    cloneAndRemoveButton(actionControlPanel, this->btnSkill1, BtnSkill1);
    cloneAndRemoveButton(actionControlPanel, this->btnSkill2, BtnSkill2);
    
    this->listAssignedWidget->addObject(this->btnLeft);
    this->listAssignedWidget->addObject(this->btnRight);
    
    //Get label and process
    lblWave  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("information_layer")->getChildByName("wave_information_panel")->getChildByName("wave_text");
    lblWave->setText("");
    lblTimeLeft  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("information_layer")->getChildByName("time_panel")->getChildByName("time_left_text");
    lblMoney  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("information_layer")->getChildByName("money_panel")->getChildByName("money_text");
    lblMonsterLeft  = (cocos2d::gui::LabelBMFont*)ul->getChildByName("information_layer")->getChildByName("wave_information_panel")->getChildByName("monster_left_text");
    lblMonsterLeft->setText("");
    
    btnPause = (cocos2d::gui::UIButton*)ul->getChildByName("information_layer")->getChildByName("time_panel")->getChildByName("pause_button");
    //
    resultImage = (cocos2d::gui::ImageView*)ul->getChildByName("result_title");
    
    //add touch event
    this->btnLeft->addTouchEventListener(this, toucheventselector(GameplayLayer::leftButtonTouchEvent));
    this->btnRight->addTouchEventListener(this, toucheventselector(GameplayLayer::rightButtonTouchEvent));
    this->btnJump->addTouchEventListener(this, toucheventselector(GameplayLayer::jumpButtonTouchEvent));
    this->btnSkill0->addTouchEventListener(this, toucheventselector(GameplayLayer::skill0ButtonTouchEvent));
    this->btnSkill1->addTouchEventListener(this, toucheventselector(GameplayLayer::skill1ButtonTouchEvent));
    this->btnSkill2->addTouchEventListener(this, toucheventselector(GameplayLayer::skill2ButtonTouchEvent));
    this->btnPause->addTouchEventListener(this, toucheventselector(GameplayLayer::pauseButtonTouchEvent));
    
    this->lvDefense = (ListView*)this->defenseListGroup->getChildByName("defense_list_panel")->getChildByName("defense_list");
    this->lvDefense->setItemsMargin(10);
    this->lvDefense->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);
    this->lvDefense->setTouchEnabled(false);
    
    this->btnOpenDefenseList =  (Button*)this->actionControlPanel->getChildByName("defense_list_open_button");
    
    this->btnOpenDefenseList->addTouchEventListener(this, toucheventselector(GameplayLayer::openDefenseListButtonTouchEvent));
    
    this->btnCloseDefenseList = (Button*)this->defenseListGroup->getChildByName("defense_list_toggle");
    
    this->btnCloseDefenseList->addTouchEventListener(this, toucheventselector(GameplayLayer::closeDefenseListButtonTouchEvent));
    
    this->lvDefense->setBounceEnabled(true);
    this->lvDefense->setInertiaScrollEnabled(false);
    
    correctPositionDefenseListGroup = this->defenseListGroup->getPosition();
    
    
}

void GameplayLayer::initUI()
{
    this->defenseListGroup->setEnabled(false);
    
    this->actionControlPanel->setEnabled(true);
}

void GameplayLayer::cloneAndRemoveButton(cocos2d::gui::Widget* ul, HoldableButton* mButton,cocos2d::gui::Button* button)
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

void GameplayLayer::setWaveValue(const char* waveName)
{
    this->lblWave->setText(CCString::createWithFormat("%s",waveName)->getCString());
}

void GameplayLayer::setMonsterProcessValue(int maxMonsterQuantity, int currentMonsterQuantity)
{
    this->lblMonsterLeft->setText(CCString::createWithFormat("%d/%d",currentMonsterQuantity,maxMonsterQuantity)->getCString());
}

bool GameplayLayer::receiveCommand(CommandID commandID, void* data)
{
    Controller::receiveCommand(commandID, data);
    switch (commandID)
    {
        case DISPLAY_NEW_WAVE:
        {
            CCString* waveName = static_cast<CCString*>(data);
            //            static_cast<char*>(data);
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            CCLabelTTF* labelStyle = CCLabelTTF::create("", "Marker Felt", 150);
            labelStyle->setOpacity(100);
            
            TextShowEffect* effect = TextShowEffect::create();
            effect->setContent(waveName->getCString());
            effect->setLabelStyle(labelStyle);
            
            EffectManager::getInstance()->runEffect(effect, ccp(size.width/2, size.height/2),this);
            setWaveValue(waveName->getCString());
            waveName->release();
        }
            break;
        case DISPLAY_RESULT:
        {
            int* result = static_cast<int*>(data);
            resultImage->setVisible(true);
            if(*result == 0)
            {
                resultImage->loadTexture("defeat_title.png",UI_TEX_TYPE_PLIST);
            }
            else
            {
                resultImage->loadTexture("victory_title.png",UI_TEX_TYPE_PLIST);
                
            }
            delete result;
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
                        setButtonDisable(this->btnSkill0, !mData->isActive);
                        break;
                    case SKILL_1_BTN:
                        setButtonDisable(this->btnSkill1, !mData->isActive);
                        break;
                    case SKILL_2_BTN:
                        setButtonDisable(this->btnSkill2, !mData->isActive);
                        
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
            setDisableUI(true);
        }
            break;
        case VISIBLE_ALL_HERO_CONTROLLER:
        {
            setDisableUI(false);
        }
            break;
        case DISPLAY_GOLD_VALUE:
        {
            int* goldValue = static_cast<int*>(data);
            refeshDefenseListView(*goldValue);
            lblMoney->setText(CCString::createWithFormat("%d", *goldValue)->getCString());
            
            delete goldValue;
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
        default:
            break;
    }
}

void GameplayLayer::skill0ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_0);
            break;
        default:
            break;
    }
}

void GameplayLayer::skill1ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_1);
            break;
        default:
            break;
    }
}

void GameplayLayer::skill2ButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_ATTACK_2);
            break;
        default:
            break;
    }
}

void GameplayLayer::openDefenseListButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            openDefenseListGroup();
            closeActionControlPanel();
            break;
        default:
            break;
    }
}

void GameplayLayer::closeDefenseListButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
            closeDefenseListGroup();
            openActionControlPanel();
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
            
            break;
        default:
            break;
    }
}

void GameplayLayer::pauseButtonTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
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
            this->getParent()->addChild(PauseLayer::create(),5);
            break;
        default:
            break;
    }
}


void GameplayLayer::openDefenseListView(bool open)
{
}

void GameplayLayer::activeDefenseList()
{
    this->defenseListGroup->setEnabled(true);
}

void GameplayLayer::deactiveDefenseList()
{
    this->defenseListGroup->setEnabled(false);
}

void GameplayLayer::activeActionControl()
{
    this->actionControlPanel->setEnabled(true);
}

void GameplayLayer::deactiveActionControl()
{
    this->actionControlPanel->setEnabled(false);
}

void GameplayLayer::activeMovingControl()
{
    this->movingControlPanel->setEnabled(true);
}

void GameplayLayer::deactiveMovingControl()
{
    this->movingControlPanel->setEnabled(false);
}

void GameplayLayer::openActionControlPanel()
{
    this->actionControlPanel->stopAllActions();
    setEnableWidgetInActionControl(false);
    activeActionControl();
    CCFadeIn* fadeIn = CCFadeIn::create(0.2f);
    
    CCCallFunc* finishAnimationCallfunc = CCCallFunc::create(this, callfunc_selector(GameplayLayer::finishAnimationOfActionControl));
    this->actionControlPanel->runAction(CCSequence::create(fadeIn, finishAnimationCallfunc, NULL ));
}

void GameplayLayer::closeActionControlPanel()
{
    this->actionControlPanel->stopAllActions();
    setEnableWidgetInActionControl(false);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    CCCallFunc* deactiveActionControl = CCCallFunc::create(this, callfunc_selector(GameplayLayer::deactiveActionControl));
    this->actionControlPanel->runAction(CCSequence::create(fadeOut, deactiveActionControl,NULL));
}

void GameplayLayer::openMovingControlPanel()
{
    this->movingControlPanel->stopAllActions();
    setEnableWidgetInMovingControl(true);
    activeMovingControl();
    CCFadeIn* fadeIn = CCFadeIn::create(0.2f);
    //
    //    CCCallFunc* finishAnimationCallfunc = CCCallFunc::create(this, callfunc_selector(GameplayLayer::finishAnimationOfActionControl));
    this->movingControlPanel->runAction(CCSequence::create(fadeIn, NULL ));
}

void GameplayLayer::closeMovingControlPanel()
{
    this->movingControlPanel->stopAllActions();
    setEnableWidgetInMovingControl(false);
    CCFadeOut* fadeOut = CCFadeOut::create(0.2f);
    CCCallFunc* deactiveActionControl = CCCallFunc::create(this, callfunc_selector(GameplayLayer::deactiveMovingControl));
    this->actionControlPanel->runAction(CCSequence::create(fadeOut, deactiveActionControl,NULL));
}


void GameplayLayer::openDefenseListGroup()
{
    this->defenseListGroup->stopAllActions();
    setEnableWidgetInDefenseListGroup(false);
    activeDefenseList();
    this->defenseListGroup->setPosition(ccp(correctPositionDefenseListGroup.x + 600,correctPositionDefenseListGroup.y));
    
    CCMoveTo* moveToOver = CCMoveTo::create(0.25f, correctPositionDefenseListGroup + ccp(-20,0));
    CCMoveTo* moveToBackOver = CCMoveTo::create(0.2f, correctPositionDefenseListGroup + ccp(5,0));
    CCMoveTo* moveToBack = CCMoveTo::create(0.1f, correctPositionDefenseListGroup);
    
    
    CCFadeIn* fadeIn = CCFadeIn::create(0.3f);
    CCCallFunc* finishAnimationCallfunc = CCCallFunc::create(this, callfunc_selector(GameplayLayer::finishAnimationOfDefenseListGroup));
    
    this->defenseListGroup->runAction(CCSequence::create(CCSpawn::create(CCSequence::create(moveToOver,moveToBackOver, moveToBack, NULL),fadeIn,NULL), finishAnimationCallfunc, NULL));
}

void GameplayLayer::closeDefenseListGroup()
{
    this->defenseListGroup->stopAllActions();
    setEnableWidgetInDefenseListGroup(false);
    CCFadeOut* fadeOut = CCFadeOut::create(0.3f);
    CCCallFunc* deactiveDefenseList = CCCallFunc::create(this, callfunc_selector(GameplayLayer::deactiveDefenseList));
    
    CCMoveTo* moveToOver = CCMoveTo::create(0.1f, correctPositionDefenseListGroup + ccp(-20,0));
    CCMoveTo* moveToGone = CCMoveTo::create(0.25f, correctPositionDefenseListGroup + ccp(600,0));
    
    CCCallFunc* finishAnimationCallfunc = CCCallFunc::create(this, callfunc_selector(GameplayLayer::finishAnimationOfDefenseListGroup));
    
    this->defenseListGroup->runAction(CCSequence::create(CCSpawn::create(CCSequence::create(moveToOver,moveToGone, NULL),fadeOut,NULL), deactiveDefenseList,finishAnimationCallfunc, NULL));
    
}

void GameplayLayer::finishAnimationOfActionControl()
{
    setEnableWidgetInActionControl(true);
}

void GameplayLayer::finishAnimationOfDefenseListGroup()
{
    this->defenseListGroup->setPosition(correctPositionDefenseListGroup);
    setEnableWidgetInDefenseListGroup(true);
}

void GameplayLayer::setEnableWidgetInDefenseListGroup(bool able)
{
    if(able)
    {
        this->lvDefense->setTouchEnabled(true);
        this->defenseListGroup->getChildByName("defense_list_toggle")->setTouchEnabled(true);
    }
    else
    {
        this->lvDefense->setTouchEnabled(false);
        this->defenseListGroup->getChildByName("defense_list_toggle")->setTouchEnabled(false);
    }
}

void GameplayLayer::setEnableWidgetInActionControl(bool able)
{
    if(able)
    {
        
        this->btnJump->setTouchEnabled(true);
        this->btnSkill0->setTouchEnabled(true);
        this->btnSkill1->setTouchEnabled(true);
        this->btnSkill2->setTouchEnabled(true);
        
    }
    else
    {
        
        this->btnJump->setTouchEnabled(false);
        this->btnSkill0->setTouchEnabled(false);
        this->btnSkill1->setTouchEnabled(false);
        this->btnSkill2->setTouchEnabled(false);
    }
}

void GameplayLayer::setEnableWidgetInMovingControl(bool able)
{
    if(able)
    {
        
        this->btnLeft->setTouchEnabled(true);
        this->btnRight->setTouchEnabled(true);
        
    }
    else
    {
        this->btnLeft->setTouchEnabled(false);
        this->btnRight->setTouchEnabled(false);
    }
}

void GameplayLayer::setButtonDisable(cocos2d::gui::Button* button, bool disable)
{
    if(disable)
    {
        button->setBright(false);
        button->setTouchEnabled(false);
    }
    else
    {
        button->setBright(true);
        button->setTouchEnabled(true);
    }
}

void GameplayLayer::loadDefenseList()
{
    this->defenseList->addObjectsFromArray(MapLoader::loadDefenseDTOList("defense_list.xml"));
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->defenseList, object)
    {
        DefenseDTO* defenseDTO = static_cast<DefenseDTO*>(object);
        
        Layout* layout = Layout::create();
        layout->setSize(CCSize(100,100));
        
        //
        //        layout->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        //        layout->setBackGroundColor(ccc3(255,0,0));
        Label* lbCost = Label::create();
        lbCost->setColor(ccc3(100,100,100));
        lbCost->setFontName("Marker Felt");
        lbCost->setFontSize(20);
        lbCost->setText(CCString::createWithFormat("%d G",defenseDTO->cost)->getCString());
        lbCost->setPosition(ccp(layout->getSize().width,0));
        Button* button = Button::create();
        
        button->ignoreContentAdaptWithSize(false);
        button->setSizeType(SIZE_PERCENT);
        button->setSizePercent(ccp(1,1));
        
        TextureSelector textureSelector = XMLButtonSelectorParser::parseData(defenseDTO->buttonID);
        
        
        button->loadTextures(textureSelector.activeTexture.c_str(), textureSelector.selectedTexture.c_str(), textureSelector.deactiveTexture.c_str(), cocos2d::gui::UI_TEX_TYPE_PLIST);
        button->setPosition(layout->getSize()/2);;
        button->setTouchEnabled(true);
        button->addTouchEventListener(this, toucheventselector(GameplayLayer::listItemTouchEvent));
        
        layout->addChild(button, 0, 1);
        layout->addChild(lbCost);
        layout->setUserData(defenseDTO);
        
        this->lvDefense->pushBackCustomItem(layout);
        
    }
    refeshDefenseListView(0);
}

void GameplayLayer::listItemTouchEvent(CCObject* sender, cocos2d::gui::TouchEventType type)
{
    switch (type) {
        case cocos2d::gui::TOUCH_EVENT_BEGAN:
        {
            DefenseDTO* defenseDTO = static_cast<DefenseDTO*>(this->lvDefense->getItem(this->lvDefense->getCurSelectedIndex())->getUserData());
            
            ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER,  HERO_CREATE_DEFENSE,defenseDTO);
        }
            break;
        case cocos2d::gui::TOUCH_EVENT_MOVED:
            break;
        case cocos2d::gui::TOUCH_EVENT_HOLD:
            break;
        case cocos2d::gui::TOUCH_EVENT_CANCELED:
            break;
        case cocos2d::gui::TOUCH_EVENT_ENDED:
        {
  
           
        }
            break;
        default:
            break;
    }
}

void GameplayLayer::refeshDefenseListView(int cost)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->lvDefense->getItems(), object)
    {
        //        Widget* wid = static_cast<Widget*>(object);
        
        Layout* layout = static_cast<Layout*>(object);
        DefenseDTO* defenseDTO = static_cast<DefenseDTO*>(layout->getUserData());
        
        if(cost < defenseDTO->cost)
        {
            Button* button = static_cast<Button*>(layout->getChildByTag(1));
            button->setBright(false);
            button->setTouchEnabled(false);
            layout->setColor(ccc3(170,170,170));
        }
        else
        {
            Button* button = static_cast<Button*>(layout->getChildByTag(1));
            button->setBright(true);
            button->setTouchEnabled(true);
            layout->setColor(ccc3(255,255,255));
        }
    }
}

void GameplayLayer::setDisableUI(bool disable)
{
    if(disable)
    {
        closeActionControlPanel();
        closeDefenseListGroup();
        closeMovingControlPanel();
    }
    else
    {
        openActionControlPanel();
        openMovingControlPanel();
    }
}