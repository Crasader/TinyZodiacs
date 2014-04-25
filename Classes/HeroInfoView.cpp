//
//  HeroInfoView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "HeroInfoView.h"
#include "Character.h"

HeroInfoView::HeroInfoView()
{
    
}

HeroInfoView::~HeroInfoView()
{
    
}

bool HeroInfoView::init()
{
    if(!GameObjectInfoView::init())
    {
        return false;
    }
    return true;
}

void HeroInfoView::update(float dt)
{
    this->healthBar->updateProgress(((Character*)this->gameObject)->getOriginCharacterData().getHealth(), ((Character*)this->gameObject)->getcharacterData().getHealth());
    this->healthBar->setPosition(this->gameObject->getPositionInPixel() + ccp(0,100));
    this->textName->setPosition(this->gameObject->getPositionInPixel() - ccp(0,100));
}

void HeroInfoView::attach(GameObject *gameObject)
{
    GameObjectInfoView::attach(gameObject);
}