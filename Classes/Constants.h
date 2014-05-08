//
//  Constants.h
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#ifndef TinyZodiacs_Constants_h
#define TinyZodiacs_Constants_h

#include "Cocos2d.h"
#include "Box2D/Box2d.h"

USING_NS_CC;
using namespace std;

#define SKILL_TYPE_0 "0"
#define SKILL_TYPE_1 "1"


#define SKILL_0_BUTTON 0
#define SKILL_1_BUTTON 1
#define SKILL_2_BUTTON 2

enum SkillTarget
{
    ENEMY,
    SEFT,
    ALLIES
};

struct TextureSelector
{
    CCSpriteFrame* activeTexture;
    CCSpriteFrame* deactiveTexture;
    CCSpriteFrame* selectedTexture;
};

struct ItemStruct
{
    string itemID;
    float chance;
};

struct GameHolder
{
    CCNode* nodeHolder;
    b2World* worldHolder;
};

#endif
