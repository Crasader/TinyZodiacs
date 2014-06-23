//
//  BonusItem.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/19/14.
//
//

#include "BonusItem.h"
#include "ItemFactory.h"

BonusItem::BonusItem()
{

}

BonusItem::~BonusItem()
{
    this->listEffectData.clear();
}

bool BonusItem::init()
{
    if(!Item::init())
    {
        return false;
    }
    return true;
}

void BonusItem::onCreate()
{
    Item::onCreate();
    
}
void BonusItem::destroy()
{
    Item::destroy();
}

void BonusItem::startSchedule()
{
    Item::startSchedule();
}

void BonusItem::prepareToAppear()
{
    Item::prepareToAppear();
}

void BonusItem::appear()
{
    Item::appear();
}

void BonusItem::prepareToDisappearInTimeOut()
{
    Item::prepareToDisappearInTimeOut();
}

void BonusItem::prepareToDisappearInContact(GameObject* contactGameObject)
{
    Item::prepareToDisappearInContact(contactGameObject);
}

void BonusItem::prepareToDisappearInOpen()
{
    Item::prepareToDisappearInOpen();
}

void BonusItem::disappear()
{
    Item::disappear();
}

void BonusItem::contact(GameObject* contactGameObject)
{
    if(contactGameObject != NULL)
    {
        if(strcasecmp(this->titleNotification.c_str(), "") != 0)
        {
            CCLabelTTF* labelStyle = CCLabelTTF::create("", "Marker Felt", 40);
            labelStyle->setColor(ccc3(255, 100, 100));
            
            TextShowEffect* effect = TextShowEffect::create();
            effect->setContent(this->titleNotification);
            
            effect->setLabelStyle(labelStyle);
            EffectManager::getInstance()->runEffect(effect, this->getPositionInPixel(), ABOVE_CHARACTER_LAYER);
        }
               GameObject* gameObject = static_cast<GameObject*>(contactGameObject);
        if(gameObject->getGameObjectID() == HERO)
        {
            Util::applyEffectFromList(this->listEffectData, gameObject);
        }
    }
    Item::contact(contactGameObject);
}

void BonusItem::open(GameObject* openGameObject)
{
}
