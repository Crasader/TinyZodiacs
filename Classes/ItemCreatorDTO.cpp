//
//  ItemCreator.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/20/14.
//
//

#include "ItemCreatorDTO.h"

ItemCreatorDTO::ItemCreatorDTO()
{
    this->max = 0;
    this->delayMin = 0;
    this->delayMax = 0;
    this->beginPositionX = 0;
    this->beginPositionY = 0;
    this->endPositionX = 0;
    this->endPositionY = 0;
}

ItemCreatorDTO::~ItemCreatorDTO()
{
    this->listItem.clear();
}

bool ItemCreatorDTO::init()
{
    return true;
}
