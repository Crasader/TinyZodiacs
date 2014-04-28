//
//  CharacterIdleState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterIdleState.h"
#include "CharacterMoveState.h"
#include "CharacterMidAirState.h"
#include "CharacterAttackState.h"
#include "CharacterJumpState.h"

CharacterIdleState::CharacterIdleState(Character* character): CharacterState(character)
{
    
}

bool CharacterIdleState::onEnterState()
{
   // CCLOG("enter idle state");
    this->character->idleAnimation->getAnimation()->setLoops(INFINITY);
    action = CCAnimate::create(this->character->idleAnimation->getAnimation());
    this->character->getSprite()->runAction(action);
    return true;
}

bool CharacterIdleState::onExitState()
{
    this->stopAction();
    return true;
}

void CharacterIdleState::update(float dt)
{
    if((this->character->getBody()->GetLinearVelocity().x > 3 || this->character->getBody()->GetLinearVelocity().x < -3))
    {
        this->character->changeState(new CharacterMoveState(this->character));
        return;
    }
    if(this->character->getBody()->GetLinearVelocity().y > 5 || this->character->getBody()->GetLinearVelocity().y < -5)
    {
        this->character->changeState(new CharacterMidAirState(this->character));
         return;
    }
}

bool CharacterIdleState::attack()
{
    return true;
}

bool CharacterIdleState::move()
{
    return true;
}

bool CharacterIdleState::jump()
{
    return true ;
}

bool CharacterIdleState::useSkill()
{
    return false;
}