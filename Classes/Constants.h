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
#include "PhysicConstants.h"

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

enum ItemType
{
    GOLD,
    BONUS,
    CONTAINER
};

enum ControllerID
{
    HERO_CONTROLLER
};

enum CommandID
{
    HERO_MOVE_LEFT,
    HERO_MOVE_RIGHT,
    HERO_MOVE_STOP,
    HERO_MOVE_JUMP,
    HERO_ATTACK_1,
    HERO_ATTACK_2,
    DISABLE_BUTTON_ATTACK,
    DISPLAY_MONSTER_COUNT
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
    float positionX;
    float positionY;
};

struct TowerStruct
{
    string id;
    float positionX;
    float positionY;
    Group group;
};

struct GameHolder
{
    CCNode* nodeHolder;
    b2World* worldHolder;
};

#endif
