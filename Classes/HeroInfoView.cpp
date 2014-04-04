//
//  HeroInfoView.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#include "HeroInfoView.h"

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
    this->healthBar->updateProgress(100, 75);
    this->healthBar->setPosition(this->gameObject->getPositionInPixel() + ccp(0,100));
    this->textName->setPosition(this->gameObject->getPositionInPixel() - ccp(0,100));
}

void HeroInfoView::attach(GameObject *gameObject)
{
    GameObjectInfoView::attach(gameObject);
}