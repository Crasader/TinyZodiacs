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

void CharacterData::applyEffect(Effect* effect, GameObject* holder)
{
    if(effect->getHealth() <0)
    {
        this->health+=(effect->getHealth()+((Character*)holder)->getcharacterData().getDefense());
        this->health = MAX(this->health,0);
    }
    else
    {
        this->health+=(effect->getHealth());
        this->health = MIN(this->health,((Character*)holder)->getOriginCharacterData().getHealth());
    }
    
    this->attack+=effect->getAttack();
    this->attack = MAX(this->attack,0);
    
    this->defense+=effect->getDefense();
    this->defense = MAX(this->defense,0);
    
    this->speed+=effect->getSpeed();
    this->speed = MAX(this->speed,0);
    
    this->jumpHeight+=effect->getJumpHeight();
    this->jumpHeight = MAX(this->jumpHeight,0);
    
    this->attackSpeed-=effect->getAttackSpeed();
    this->attackSpeed = MAX(this->attackSpeed,0);
    
    this->maxJumpTimes+=effect->getMaxJump();
    this->maxJumpTimes = MAX(this->maxJumpTimes,0);
}