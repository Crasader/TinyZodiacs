//
//  GameMatch.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/22/14.
//
//

#include "GameMatch.h"
#include "MapCreator.h"


GameMatch::GameMatch()
{
    this->gameWorld = NULL;
    this->currentWave = -1;
    this->oldWave = -1;
    this->isStopped = false;
}

GameMatch::~GameMatch()
{
    
}

bool GameMatch::init()
{
    this->gameWorld = GameWorld::create();
    this->gameWorld->setMapID(DataCollector::getInstance()->getMatchData()->mapIDSelected.c_str());
    this->gameWorld->onCreate();
    this->addChild(this->gameWorld);
   
    this->player = Player::create();
    this->player->attachWithHero(DataCollector::getInstance()->getMatchData()->heroIDSelected.c_str() );
    this->addChild(this->player);
    
    this->gameWorld->addHero(this->player->getHero());
    this->rule = new Rule1();
    this->schedule(schedule_selector(GameMatch::updateToCheckMatch),1);
    
    return true;
}

void GameMatch::update(float dt)
{
    
}
void GameMatch::updateToCheckMatch()
{
    if(this->isStopped == false)
    {
        if( this->currentWave < this->gameWorld->getMap()->getListWave()->count())
        {
            ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->update(0);
        }
        
        displayMonsterCount();
        
        checkWin();
        checkLose();
        checkNextWave();
    }
}

void GameMatch::start()
{
    nextWave();
}

void GameMatch::stop()
{
    this->isStopped = true;
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->gameWorld->getMap()->getListWave(), object)
    {
        Wave* wave = static_cast<Wave*>(object);
        wave->stop();
    }
}

void GameMatch::nextWave()
{
    prepareToExitWave();
    this->oldWave = this->currentWave;
    
    if(this->oldWave == this->gameWorld->getMap()->getListWave()->count() - 1)
    {
        RuleManager::getInstance()->addRuleEvent(RULE_EVENT_COMPLETE_ALL_WAVE, true);
        return;
    }
    
    this->currentWave++;
    prepareToEnterNewWave();
    
    RuleManager::getInstance()->addRuleEvent(RULE_EVENT_COMPLETE_KILL_ALL_MONSTER_IN_WAVE, false);
}

bool GameMatch::checkWin()
{
    if(this->rule->checkWin())
    {
        //do something;
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_RESULT ,new int(1));
        
    }
    return false;
}

bool GameMatch::checkLose()
{
    
    if(this->rule->checkLose())
    {
        //do something;
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_RESULT ,new int(0));
        stop();
        ItemFactory::getInstance()->setIsActive(false);
        this->gameWorld->destroy();
        this->removeFromParent();
        
        CCDirector::sharedDirector()->popScene();
    }
    
    return false;
}

bool GameMatch::checkNextWave()
{
    if(this->rule->checkNextWave())
    {
        nextWave();
    }
    return false;
}

void GameMatch::prepareToEnterNewWave()
{
    float delay = 5;
    CCCallFunc* enterWaveFunction = CCCallFunc::create(this, callfunc_selector(GameMatch::enterWave));
    ScheduleManager::getInstance()->scheduleFunction(enterWaveFunction, NULL, delay, 1);
}

void GameMatch::prepareToExitWave()
{
    CCCallFunc* exitWaveFunction = CCCallFunc::create(this, callfunc_selector(GameMatch::exitWave));
    //    ScheduleManager::getInstance()->scheduleFunction(exitWaveFunction, NULL, 0, 1);
    ScheduleManager::getInstance()->runAction(exitWaveFunction);
    
}

void GameMatch::enterWave()
{
    if( this->currentWave < this->gameWorld->getMap()->getListWave()->count())
    {
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_NEW_WAVE, new int(this->currentWave+1));
        ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->start();
    }
}

void GameMatch::exitWave()
{
    if(this->oldWave >= 0 && this->oldWave < this->gameWorld->getMap()->getListWave()->count())
    {
        ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->oldWave))->stop();
    }
}

void GameMatch::displayMonsterCount()
{
    if(currentWave < this->gameWorld->getMap()->getListWave()->count())
    {
        int a = ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->getMonsterCountKilled();
        int b = ((Wave*)this->gameWorld->getMap()->getListWave()->objectAtIndex(this->currentWave))->getMonsterCountMax();
        
        if(b-a < 0)
        {
            assert(0);
        }
        vector<int>* arr = new vector<int>();
        arr->push_back(a);
        arr->push_back(b);
        
        ControllerManager::getInstance()->sendCommand(HERO_CONTROLLER, DISPLAY_MONSTER_COUNT,arr);
    }
}

void GameMatch::initHeroPosition()
{
    
}