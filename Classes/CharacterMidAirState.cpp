//
//  CharacterMidAirState.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "CharacterMidAirState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"
#include "CharacterAttackState.h"

CharacterMidAirState::CharacterMidAirState(Character* character): CharacterState(character)
{
    isFalling = false;
    isFlying = false;
}

bool CharacterMidAirState::onEnterState()
{
    return true;
}

bool CharacterMidAirState::onExitState()
{
    stopAction();
    return true;
}

void CharacterMidAirState::update(float dt)
{
    if(this->character->getBody()->GetLinearVelocity().y < -3 && isFalling == false)
    {
        isFalling = true;
        
        stopAction();
        //fall Action
        this->action = CCAnimate::create(this->character->fallAnimation->getAnimation());
           this->action->retain();
        this->character->getSprite()->runAction(this->action);
       
        return;
    }
    else if(this->character->getBody()->GetLinearVelocity().y > 3 && isFlying == false)
    {
        isFlying = true;
        
        stopAction();
        //fly action
        this->action = CCAnimate::create(this->character->flyAnimation->getAnimation());
           this->action->retain();
        this->character->getSprite()->runAction(this->action);
       
        return;
        
    }
    else if(this->character->getLanding())
    {
        this->character->changeState(new CharacterIdleState(this->character));
  
        return;
    }
    else
    {
       
    }
}

bool CharacterMidAirState::attack()
{
    return true;
}

bool CharacterMidAirState::move()
{
    return true;
}

bool CharacterMidAirState::jump()
{
    return true;
}

bool CharacterMidAirState::useSkill()
{
    return false;
}