//
//  CharacterMoveState.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/8/14.
//
//

#include "CharacterMoveState.h"
#include "CharacterJumpState.h"
#include "CharacterMidAirState.h"
#include "CharacterIdleState.h"

USING_NS_CC;

CharacterMoveState::CharacterMoveState(Character* character): CharacterState(character)
{
    
}

bool CharacterMoveState::onEnterState()
{
    this->character->runAnimation->getAnimation()->setLoops(INFINITY);
    this->character->getSprite()->stopAllActions();
    this->character->getSprite()->runAction(CCAnimate::create(this->character->runAnimation->getAnimation()));
    this->character->setAnchorPointForAnimation(this->character->runAnimation->getOrigin());
    
    return true;
}

bool CharacterMoveState::onExitState()
{
    this->character->getSprite()->stopAllActions();
    return true;
}

void CharacterMoveState::update(float dt)
{
    if((this->character->getBody()->GetLinearVelocity().x < 2 && this->character->getBody()->GetLinearVelocity().x >-2))
    {
        this->character->changeState(new CharacterIdleState(this->character));
        return;
    }
    if(this->character->getBody()->GetLinearVelocity().y > 2|| this->character->getBody()->GetLinearVelocity().y < -2)
    {
        this->character->changeState(new CharacterMidAirState(this->character));
    }
}

bool CharacterMoveState::attack()
{
    return false;
}

bool CharacterMoveState::move()
{
    return false;
}

bool CharacterMoveState::jump()
{
    return false;
}

bool CharacterMoveState::useSkill()
{
    return false;
}
