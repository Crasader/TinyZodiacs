//
//  NormalAttack.h
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#ifndef __TinyZodiacs__NormalAttack__
#define __TinyZodiacs__NormalAttack__

#include <iostream>
#include "Box2D.h"
#include "cocos2d.h"
//#include "Character.h"

class Character;

USING_NS_CC;
class NormalAttack
{
private:
protected:
public:
    NormalAttack();
    NormalAttack(Character* character);
    ~NormalAttack();
    
    void excute();
    void deExcute();
    
    CC_SYNTHESIZE(Character* , character, Character);
    CC_SYNTHESIZE(b2Body*, skillSensor, SkillSensor);
    CC_SYNTHESIZE(CCPoint, position, Position) //Position
};
#endif /* defined(__TinyZodiacs__NormalAttack__) */
