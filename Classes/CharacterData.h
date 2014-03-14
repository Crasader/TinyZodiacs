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

USING_NS_CC;
class CharacterData: public ObjectData
{
private:
protected:
public:
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, attack, Attack);
    CC_SYNTHESIZE(int, defense, Defense);
    CC_SYNTHESIZE(int, speed, Speed);
    CC_SYNTHESIZE(int, jumpHeight, JumpHeight);
    CC_SYNTHESIZE(int, attackSpeed, AttackSpeed);
};

#endif /* defined(__Headball__CharacterData__) */
