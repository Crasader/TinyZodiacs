//
//  InfoViewCreator.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__InfoViewCreator__
#define __TinyZodiacs__InfoViewCreator__

class InfoViewCreator;

#include <iostream>
#include "cocos2d.h"
#include "GameObjectView.h"
#include "Player.h"
#include "Hero.h"
#include "GameObjectViewContainer.h"
#include "Monster.h"

USING_NS_CC;

class InfoViewCreator
{
private:
protected:
public:
    static GameObjectView* createHeroView(Hero* hero, Player* player);
    static GameObjectView* createMonsterView(Monster* monster, Player* player);
};

#endif /* defined(__TinyZodiacs__InfoViewCreator__) */
