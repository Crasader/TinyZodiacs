//
//  ItemFactory.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/8/14.
//
//

#include "ItemFactory.h"

static ItemFactory* instance = NULL;

ItemFactory::ItemFactory()
{
    this->listItem = CCArray::create();
    this->listItem->retain();
}

ItemFactory::~ItemFactory()
{
    
}

ItemFactory* ItemFactory::getInstance()
{
    if(instance == NULL)
    {
        instance = new ItemFactory();
    }
    return instance;
}

void ItemFactory::setHolder(GameHolder* holder)
{
    this->holder = holder;
}

void ItemFactory::createItem(const char* id, CCPoint position)
{
    Item* item = ObjectFactory::getSharedManager()->createItem(DataCollector::getInstance()->getItemDTOByKey(id), this->holder->worldHolder);
    item->setPositionInPixel(position);
    this->holder->nodeHolder->addChild(item->getSprite(),ABOVE_CHARACTER_LAYER);
    this->listItem->addObject(item);
    
    item->getBody()->SetLinearVelocity(b2Vec2(CCRANDOM_MINUS1_1()*3,7));
}

void ItemFactory::update(float dt)
{
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listItem, object)
    {
        Item* item = static_cast<Item*>(object);
        item->update(dt);
    }
}

void ItemFactory::destroyItem(Item* item)
{
    this->listItem->removeObject(item);
}

