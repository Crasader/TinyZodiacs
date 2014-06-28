//
//  InfoViewCreator.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "InfoViewCreator.h"
#include "CharacterView.h"
#include "HealthBar.h"

GameObjectView* InfoViewCreator::createHeroView(Hero* hero, Player* player)
{
    GameObjectViewContainer* view = GameObjectViewContainer::create();
    view->retain();
    
    CharacterView* heroView = CharacterView::create();

    
    HealthBar* healthBar = HealthBar::create();
    
    if(hero->getGroup() == A)
    {
        healthBar->setForeground("healthbar_blue.png");
    }
    else
    {
        healthBar->setForeground("healthbar_red.png");

    }
    
    CCLabelTTF* label = CCLabelTTF::create("Hoa Phat", "Marker Felt", 25);
    
    heroView->setHealthBar(healthBar);
   // heroView->setTextNameLabel(label);

    view->attach(hero);
    view->addGameObjectView(heroView);
    
    return view;
}

GameObjectView* InfoViewCreator::createMonsterView(Monster* monster, Player* player)
{
    GameObjectViewContainer* view = GameObjectViewContainer::create();
    view->retain();
    
    CharacterView* heroView = CharacterView::create();
    
    
    HealthBar* healthBar = HealthBar::create();
    
    if(monster->getGroup() == A)
    {
        healthBar->setForeground("healthbar_blue.png");
    }
    else
    {
        healthBar->setForeground("healthbar_red.png");
        
    }
    
    CCLabelTTF* label = CCLabelTTF::create("monster", "Marker Felt", 25);
    
    heroView->setHealthBar(healthBar);
   // heroView->setTextNameLabel(label);
    
    view->attach(monster);
    view->addGameObjectView(heroView);
    
    return view;
}

GameObjectView* InfoViewCreator::createTowerView(Tower* tower, Player* player)
{
    GameObjectViewContainer* view = GameObjectViewContainer::create();
    view->retain();
    
    CharacterView* towerView = CharacterView::create();
    
    
    HealthBar* healthBar = HealthBar::create();
    
    if(tower->getGroup() == A)
    {
        healthBar->setForeground("healthbar_blue.png");
    }
    else
    {
        healthBar->setForeground("healthbar_red.png");
        
    }
    
    towerView->setHealthBar(healthBar);
    
    view->attach(tower);
    view->addGameObjectView(towerView);
    
    return view;
}