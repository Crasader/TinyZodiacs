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
    return false;
}

bool CharacterMidAirState::onExitState()
{
    this->character->getSprite()->stopAllActions();
    return true;
}

void CharacterMidAirState::update(float dt)
{
    if(this->character->getBody()->GetLinearVelocity().y < -2 && isFalling == false)
    {
        isFalling = true;
        
        this->character->getSprite()->stopAllActions();
        this->character->fallAnimation->getAnimation()->setLoops(INFINITY);
        CCAction* fallAction = CCAnimate::create(this->character->fallAnimation->getAnimation());
        this->character->getSprite()->runAction(fallAction);
        this->character->setAnchorPointForAnimation( this->character->fallAnimation->getOrigin());
        
    }
    else if(this->character->getBody()->GetLinearVelocity().y >2 && isFlying == false)
    {
        isFlying = true;
        
        this->character->getSprite()->stopAllActions();
        this->character->flyAnimation->getAnimation()->setLoops(INFINITY);
        CCAction* flyAction = CCAnimate::create(this->character->flyAnimation->getAnimation());
        this->character->getSprite()->runAction(flyAction);
        this->character->setAnchorPointForAnimation( this->character->flyAnimation->getOrigin());
        
    }
//    if (this->character->getBody()->GetLinearVelocity().y <2 && this->character->getBody()->GetLinearVelocity().y > -2 &&  isFalling == true)
//    {
//        this->character->changeState(new CharacterIdleState(this->character));
//    }
    if(this->character->getLanding())
    {
        this->character->changeState(new CharacterIdleState(this->character));
    }
}

bool CharacterMidAirState::attack()
{
    this->character->changeState(new CharacterAttackState(this->character));

    return true;
}

bool CharacterMidAirState::move()
{
    return true;
}

bool CharacterMidAirState::jump()
{
    this->character->changeState(new CharacterJumpState(this->character));
    return true;
}

bool CharacterMidAirState::useSkill()
{
    return false;
}