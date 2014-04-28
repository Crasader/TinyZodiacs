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

#define MAP_BASE 0
#define CHARACTER_BODY -1
#define CHARACTER_FOOT_SENSOR -2
#define PROJECTILE 1
#define SKILL_SENSOR 2
#define TOWER_SENSOR 4
#define MAP_SENSOR 3


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

enum Group
{
    A,
    B,
    NEUTRAL,
    TERRAIN
};

#endif
