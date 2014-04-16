//
//  MonsterFactory.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/15/14.
//
//

#include "MonsterFactory.h"

static MonsterFactory* sharedFactory = NULL;

MonsterFactory::MonsterFactory()
{
    
}

MonsterFactory::~MonsterFactory()
{
    delete sharedFactory;
}

MonsterFactory* MonsterFactory::getSharedFactory()
{
    if (!sharedFactory)
    {
        sharedFactory = new MonsterFactory();
    }
    return sharedFactory;
}

Monster* MonsterFactory::createMonster(b2World* world)
{
    Monster* monster = NULL;
    return monster;
}


