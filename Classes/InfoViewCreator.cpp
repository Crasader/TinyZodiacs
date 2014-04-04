//
//  InfoViewCreator.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "InfoViewCreator.h"
#include "HeroInfoView.h"
#include "HealthBar.h"

GameObjectInfoView* InfoViewCreator::createHeroInfoView(Character *character, Player *player)
{
    HealthBar* healthBar = HealthBar::create();
    healthBar->retain();
    
    GameObjectInfoView* heroInfoView = HeroInfoView::create();
    heroInfoView->attach(character);
    
    
    //Label;
    
    CCLabelTTF* textName = CCLabelTTF::create("Hoa Phat", "Arial", 15);
    textName->retain();
    heroInfoView->setHealthBar(healthBar);

    heroInfoView->setTextName(textName);
    
    
    return heroInfoView;
}