
//
//  ContainerItem.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#include "ContainerItem.h"
#include "ItemFactory.h"

ContainerItem::ContainerItem()
{
    isOpened = false;
}

ContainerItem::~ContainerItem()
{
    CCLOG("des container");
}

bool ContainerItem::init()
{
    if(!Item::init())
    {
        return false;
    }
    return true;
}

void ContainerItem::onCreate()
{
    Item::onCreate();
}
void ContainerItem::destroy()
{
    Item::destroy();
}

void ContainerItem::startSchedule()
{
    Item::startSchedule();
}

void ContainerItem::prepareToAppear()
{
    Item::prepareToAppear();
}

void ContainerItem::appear()
{
    Item::appear();
}

void ContainerItem::prepareToDisappearInTimeOut()
{
    Item::prepareToDisappearInTimeOut();
}

void ContainerItem::prepareToDisappearInContact(GameObject* contactGameObject)
{
    Item::prepareToDisappearInContact(contactGameObject);
}

void ContainerItem::prepareToDisappearInOpen()
{
    Item::prepareToDisappearInOpen();
}

void ContainerItem::disappear()
{
    Item::disappear();
}

void ContainerItem::contact(GameObject* contactGameObject)
{
   // Item::contact(contactGameObject);
}

void ContainerItem::open(GameObject* openGameObject)
{
    if(this->isDestroyed || openGameObject == NULL)
    {
        return;
    }
    if(openGameObject->getGameObjectID() == HERO)
    {
        Item::open(openGameObject);
        if(this->isOpened == false)
        {
            for(int i=0; i<this->listSubItem.size(); i++)
            {
                ItemStruct itemStruct = this->listSubItem[i];
                itemStruct.positionX = this->getPositionInPixel().x;
                itemStruct.positionY = this->getPositionInPixel().y;
                ItemFactory::getInstance()->addItemPrepareToCreate(itemStruct);
            }
            
            this->isOpened = true;
            Item::prepareToDisappearInOpen();
        }
    }
}

