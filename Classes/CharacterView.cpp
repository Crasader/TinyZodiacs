//
//  HeroInfoView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "CharacterView.h"

CharacterView::CharacterView()
{
    this->healthBar = NULL;
    this->textNameLabel = NULL;
}

CharacterView::~CharacterView()
{
    
}

bool CharacterView::init()
{
    if(!GameObjectView::init())
    {
        return false;
    }
    return true;
}

void CharacterView::update(float dt)
{
        this->healthBar->setPosition(this->gameObject->getPositionInPixel() + ccp(0,100));
    this->textNameLabel->setPosition(this->gameObject->getPositionInPixel() - ccp(0,100));
}

void CharacterView::attach(GameObject *gameObject)
{
    GameObjectView::attach(gameObject);
}

void CharacterView::setHealthBar(HealthBar* healthBar)
{
    this->healthBar = healthBar;
    this->addChild(this->healthBar);
}

void CharacterView::setTextNameLabel(CCLabelTTF* textNameLabel)
{
    this->textNameLabel = textNameLabel;
    this->addChild(this->textNameLabel);
}

void CharacterView::notifyChange()
{
    this->healthBar->updateProgress(((Hero*)this->gameObject)->getOriginCharacterData().getHealth(), ((Hero*)this->gameObject)->getcharacterData().getHealth());
}