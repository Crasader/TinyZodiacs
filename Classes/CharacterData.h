//
//  CharacterData.h
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#ifndef __Headball__CharacterData__
#define __Headball__CharacterData__

#include <iostream>
#include "ObjectData.h"
#include "cocos2d.h"
#include "Affect.h"
#include "GameObject.h"

USING_NS_CC;
class CharacterData: public ObjectData
{
private:
protected:
public:
    CharacterData();
    ~CharacterData();
    
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, attack, Attack);
    CC_SYNTHESIZE(int, defense, Defense);
    
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(float, jumpHeight, JumpHeight);
    CC_SYNTHESIZE(float, attackSpeed, AttackSpeed);
    CC_SYNTHESIZE(int, maxJumpTimes, MaxJumpTimes);
    
    CC_SYNTHESIZE(std::string, skill0, Skill0);
    CC_SYNTHESIZE(std::string, skill1, Skill1);
    CC_SYNTHESIZE(std::string, skill2, Skill2);

    void setData(CharacterData data);
    void applyData(CharacterData data);
    void applyAffect(Affect* affect, GameObject* holder);
};

#endif /* defined(__Headball__CharacterData__) */
