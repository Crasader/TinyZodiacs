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
#include "Util.h"

CharacterMidAirState::CharacterMidAirState(Character* character): CharacterState(character)
{
    isFalling = false;
    isFlying = false;
    oldFriction = 0;
}

bool CharacterMidAirState::onEnterState()
{
//    for (b2Fixture* f = this->character->getBody()->GetFixtureList(); f; f = f->GetNext())
//    {
//        f->SetFriction(0);
//    }
    return true;
}

bool CharacterMidAirState::onExitState()
{
//    for (b2Fixture* f = this->character->getBody()->GetFixtureList(); f; f = f->GetNext())
//    {
//        f->SetFriction(100);
//    }
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
        
        if(this->character->fallAnimation != NULL)
        {
            CCAnimation* animation = Util::getAnimationFromAnimationObject(this->character->fallAnimation);
            if(animation != NULL)
            {
                this->action = CCAnimate::create(animation);
                this->action->retain();
                this->character->getSprite()->runAction(this->action);
            }
        }
           
        return;
    }
    else if(this->character->getBody()->GetLinearVelocity().y > 3 && isFlying == false)
    {
        isFlying = true;
        
        stopAction();
        //fly action
        if(this->character->flyAnimation != NULL)
        {
            CCAnimation* animation = Util::getAnimationFromAnimationObject(this->character->flyAnimation);
            if(animation != NULL)
            {
                this->action = CCAnimate::create(animation);
                this->action->retain();
                this->character->getSprite()->runAction(this->action);
            }
        }
       
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