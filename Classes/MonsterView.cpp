//
//  MonsterView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/15/14.
//
//

#include "MonsterView.h"

MonsterView::MonsterView()
{
    this->healthBar = NULL;
    this->textNameLabel = NULL;
}

MonsterView::~MonsterView()
{
    
}

bool MonsterView::init()
{
    if(!GameObjectView::init())
    {
        return false;
    }
    return true;
}

void MonsterView::update(float dt)
{
    //    this->healthBar->updateProgress(((Hero*)this->gameObject)->getOriginCharacterData().getHealth(), ((Hero*)this->gameObject)->getcharacterData().getHealth());
    this->healthBar->setPosition(this->gameObject->getPositionInPixel() + ccp(0,100));
    this->textNameLabel->setPosition(this->gameObject->getPositionInPixel() - ccp(0,100));
}

void MonsterView::attach(GameObject *gameObject)
{
    GameObjectView::attach(gameObject);
}

void MonsterView::setHealthBar(HealthBar* healthBar)
{
    this->healthBar = healthBar;
    this->addChild(this->healthBar);
}

void MonsterView::setTextNameLabel(CCLabelTTF* textNameLabel)
{
    this->textNameLabel = textNameLabel;
    this->addChild(this->textNameLabel);
}