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
#define FOOT_SENSOR_HEIGHT 10/32

#define MAP_BASE 0
#define CHARACTER_BODY -1
#define CHARACTER_FOOT_SENSOR -2
#define PROJECTILE 1
#define SKILL_SENSOR 2

#define JOINT_CENTER 0
#define JOINT_TOP_OR_RIGHT 1
#define JOINT_BOTTOM_OR_LEFT -1
#define JOINT_REAR 2

struct JointDef
{
    int x;
    int y;
    int offsetX;
    int offsetY;
};

#endif
