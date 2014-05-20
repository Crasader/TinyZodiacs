//
//  GoldItem.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#include "GoldItem.h"

GoldItem::GoldItem()
{
    
}

GoldItem::~GoldItem()
{
    
}

bool GoldItem::init()
{
    if(!Item::init())
    {
        return false;
    }
    return true;
}

void GoldItem::onCreate()
{
    Item::onCreate();
}
void GoldItem::destroy()
{
    Item::destroy();
}

void GoldItem::startSchedule()
{
    Item::startSchedule();
}

void GoldItem::prepareToAppear()
{
    Item::prepareToAppear();
}

void GoldItem::appear()
{
    Item::appear();
}

void GoldItem::prepareToDisappearInTimeOut()
{
    Item::prepareToDisappearInTimeOut();
}

void GoldItem::prepareToDisappearInContact(GameObject* contactGameObject)
{
    Item::prepareToDisappearInContact(contactGameObject);
}

void GoldItem::prepareToDisappearInOpen()
{
    Item::prepareToDisappearInOpen();
}

void GoldItem::disappear()
{
    Item::disappear();
}

void GoldItem::contact(GameObject* contactGameObject)
{
    Item::contact(contactGameObject);
}

void GoldItem::open(GameObject* openGameObject)
{
}
