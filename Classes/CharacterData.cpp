//
//  CharacterData.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterData.h"
#include "Character.h"

CharacterData::CharacterData()
{
    
}

CharacterData::~CharacterData()
{
    
}

void CharacterData::setData(CharacterData data)
{
//    this->health=data.health;
    this->attack=data.attack;
    this->defense=data.defense;
    
    this->speed=data.speed;
    this->jumpHeight=data.jumpHeight;
    this->attackSpeed=data.attackSpeed;
    this->maxJumpTimes=data.maxJumpTimes;
}

void CharacterData::applyData(CharacterData data, CharacterData originalData)
{
    this->attack=data.attack;
    this->attack = MAX(this->attack,0);
    
    this->defense=data.defense;
    this->defense = MAX(this->defense,0);
    
    this->speed=data.speed;
    this->speed = MAX(this->speed,0);
    
    this->jumpHeight=data.jumpHeight;
    this->jumpHeight = MAX(this->jumpHeight,0);
    
    this->attackSpeed=data.attackSpeed;
    this->attackSpeed = MAX(this->attackSpeed,0);
    
    this->maxJumpTimes=data.maxJumpTimes;
    this->maxJumpTimes = MAX(this->maxJumpTimes,0);
    
    if(data.getHealth()>0)
    {
        this->health+= data.health;
        this->health = MIN(this->health,originalData.getHealth());
    }
    else
    {
        this->health+= MIN((data.getHealth()+this->getDefense()),0);
    }
        //    this->health = MAX(this->health,0);
}

void CharacterData::applyAffect(Affect* affect, GameObject* holder)
{
    if(affect->getHealth() <0)
    {
        this->health+=MIN((affect->getHealth()+((Character*)holder)->getcharacterData().getDefense()),0);
    }
    else
    {
        this->health+=(affect->getHealth());
        this->health = MIN(this->health,((Character*)holder)->getOriginCharacterData().getHealth());
    }
    
    this->attack+=affect->getAttack();
    this->attack = MAX(this->attack,0);
    
    this->defense+=affect->getDefense();
    this->defense = MAX(this->defense,0);
    
    this->speed+=affect->getSpeed();
    this->speed = MAX(this->speed,0);
    
    this->jumpHeight+=affect->getJumpHeight();
    this->jumpHeight = MAX(this->jumpHeight,0);
    
    this->attackSpeed-=affect->getAttackSpeed();
    this->attackSpeed = MAX(this->attackSpeed,0);
    
    this->maxJumpTimes+=affect->getMaxJump();
    this->maxJumpTimes = MAX(this->maxJumpTimes,0);
}

CharacterData CharacterData::getRawData()
{
    CharacterData data;
    data.health=0;
    data.attack=0;
    data.defense=0;
    data.speed=0;
    data.jumpHeight=0;
    data.attackSpeed=0;
    data.maxJumpTimes=0;
    return data;
}

CharacterData CharacterData::operator+(const CharacterData& other)
{
    CharacterData data;
    data.health=this->health + other.health;
    data.attack=this->attack + other.attack;
    data.defense=this->defense + other.defense;
    data.speed=this->speed + other.speed;
    data.jumpHeight=this->jumpHeight + other.jumpHeight;
    data.attackSpeed=this->attackSpeed + other.attackSpeed;
    data.maxJumpTimes=this->maxJumpTimes + other.maxJumpTimes;
    
    return data;
}