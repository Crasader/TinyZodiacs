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

enum Direction {LEFT, RIGHT};

enum CharacterSkill
{
    NORMAL_ATTACK,
    SKILL_1,
    SKILL_2
};

enum SkillTarget
{
    ENEMY,
    SEFT,
    ALLIES
};

enum ButtonID
{
    UNKNOWN,
    SKILL_0_BTN,
    SKILL_1_BTN,
    SKILL_2_BTN
};

enum ItemType
{
    GOLD,
    BONUS,
    CONTAINER
};

enum ControllerID
{
    HERO_CONTROLLER,
    OBJECT_CONTROLLER,
    GAME_MATCH_CONTROLLER
};

enum CommandID
{
    HERO_CREATE_DEFENSE,
    HERO_MOVE_LEFT,
    HERO_MOVE_RIGHT,
    HERO_MOVE_STOP,
    HERO_MOVE_JUMP,
    HERO_ATTACK_0,
    HERO_ATTACK_1,
    HERO_ATTACK_2,
    DISABLE_BUTTON_ATTACK,
    DISPLAY_MONSTER_COUNT,
    DISPLAY_NEW_WAVE,
    DISPLAY_WORLD_COORDINATE,
    CHANGE_SKILL_0_TEXTURE_SET,
    CHANGE_SKILL_1_TEXTURE_SET,
    CHANGE_SKILL_2_TEXTURE_SET,
    CHANGE_STATE,
    INVISIBLE_ALL_HERO_CONTROLLER,
    VISIBLE_ALL_HERO_CONTROLLER,
    CAMERA_FOLLOW_POINTER,
    DISPLAY_RESULT,
    DISPLAY_GOLD_VALUE,
    QUIT_GAME
};



struct TextureSelector
{
    std::string activeTexture;
    std::string deactiveTexture;
    std::string selectedTexture;
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


enum CharacterSound
{
    HURT_SOUND,
    DEATH_SOUND,
    JUMP_SOUND
};

enum ProjectileSound
{
    CREATE_SOUND,
    SHOOT_SOUND,
    DIE_SOUND,
    HIT_SOUND
};

//enum SkillSound
//{
//    EXCUTE_SOUND,
//    STOP_SOUND,
//    SKILL_HIT_SOUND
//};

enum SkillState
{
    CREATED,
    PRE_EXCUTE,
    EXCUTE,
    PRE_STOP,
    STOP,
    HIT
};

enum ItemSound
{
    APPEAR,
    DISAPPEAR,
    DESTROY,
    CONSUME
};

enum SoundType
{
    MUSIC,
    SOUND_EFFECT
};

enum ProjectileAngleType
{
    HOLDER_DIRECTION,
    FREE_STYLE
};

enum ApplyType
{
    DO_NOT_APPLY=-1,
    APPLY_ONCE =0,
    APPLY_OVERTIME =1
};

class SoundStruct
{
public:
    std::string soundId;
    SoundType type;
};

class StateCommandData
{
public:
    ButtonID controllerId;
    bool isActive;
};
#endif
