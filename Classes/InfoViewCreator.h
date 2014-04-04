//
//  InfoViewCreator.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__InfoViewCreator__
#define __TinyZodiacs__InfoViewCreator__

#include <iostream>
#include "cocos2d.h"
#include "GameObjectInfoView.h"
#include "Player.h"
#include "Character.h"

USING_NS_CC;


class InfoViewCreator
{
private:
protected:
public:
    static GameObjectInfoView* createHeroInfoView(Character* character, Player* player);
};

#endif /* defined(__TinyZodiacs__InfoViewCreator__) */
