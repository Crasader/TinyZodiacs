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

void CharacterData::applyData(CharacterData data)
{
    this->health+=data.health;
    this->health = MAX(this->health,0);
    
    this->attack+=data.attack;
    this->attack = MAX(this->attack,0);
    
    this->defense+=data.defense;
    this->defense = MAX(this->defense,0);
    
    this->speed+=data.speed;
    this->speed = MAX(this->speed,0);
    
    this->jumpHeight+=data.jumpHeight;
    this->jumpHeight = MAX(this->jumpHeight,0);
    
    this->attackSpeed+=data.attackSpeed;
    this->attackSpeed = MAX(this->attackSpeed,0);
    
    this->maxJumpTimes+=data.maxJumpTimes;
    this->maxJumpTimes = MAX(this->maxJumpTimes,0);
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