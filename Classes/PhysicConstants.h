//
//  PhysicConstants.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef Headball_PhysicConstants_h
#define Headball_PhysicConstants_h

#define PTM_RATIO 32
#define GRAVITY_ACCELERATION_X 0
#define GRAVITY_ACCELERATION_Y -10
#define WEIGHTLESS_DENSITY 0.00001
#define FOOT_SENSOR_WIDTH 10/32
#define FOOT_SENSOR_HEIGHT 5/32

#define JOINT_CENTER 0
#define JOINT_TOP_OR_RIGHT 1
#define JOINT_BOTTOM_OR_LEFT -1
#define JOINT_REAR 2

#define GROUP_A 0x0002
#define GROUP_B 0x0004
#define GROUP_NEUTRUAL 0x0008
#define GROUP_TERRAIN 0x0010
#define GROUP_HERO_A 0x0020
#define GROUP_HERO_B 0x0040
#define GROUP_SKILL_DEFAULT 0x0080
#define GROUP_SENSOR 0x0100
#define GROUP_TOWER_A 0x0200
#define GROUP_TOWER_B 0x0400
#define GROUP_MONSTER_SENSOR 0x0800
#define GROUP_ITEM 0x1000
#define GROUP_WALL 0x2000

//#define GROUP_TOWER 0x0200

#define RADIUS_TOWER_SENSOR 500/32
#define TOWER_VELOCITY 1


struct JointDef
{
    int x;
    int y;
    float offsetX;
    float offsetY;
};

enum BodyId
{
    MAP_BASE ,
    CHARACTER_BODY ,
    CHARACTER_FOOT_SENSOR ,
    PROJECTILE ,
    SKILL_SENSOR ,
    TOWER_SENSOR ,
    MAP_SENSOR ,
    MONSTER_SENSOR,
    GAME_ITEM,
    WALL_BODY
};

enum GameObjectID
{
    NONE,
    HERO,
    MONSTER,
    MAP_OBJECT,
    SKILL_OBJECT,
    TOWER,
    ITEM,
    PROJECTILE_OBJECT,
    GOLD_ITEM,
    WALL
};

enum FixtureID
{
    FOOT_SENSOR,
    BODY_MAIN_FIXTURE,
    BODY_SUB_FIXTURE,
    SKILL_FIXTURE,
    MONSTER_SENSOR_FIXTURE,
    TOWER_SENSOR_FIXTURE,
    PROJECTILE_FIXTURE,
    FOOT_SENSOR_FIXTURE,
    MAP_OBJECT_FIXTURE
};

enum Group
{
    A,
    B,
    NEUTRAL,
    TERRAIN,
    ITEM_GROUP
};

enum RuleEventID
{
    RULE_EVENT_COMPLETE_KILL_ALL_MONSTER_IN_WAVE,
    RULE_EVENT_MAIN_CRYSTAL_DESTROYED,
    RULE_EVENT_BOSS_HAVE_BEEN_KILLED,
    RULE_EVENT_COMPLETE_ALL_WAVE
};

enum ProjectileAngle
{
    ABSOLUTE_LEFT =0,
    ABSOLUTE_RIGHT=180
};
#endif
