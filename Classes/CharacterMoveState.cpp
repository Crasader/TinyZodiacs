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
#include "CharacterAttackState.h"

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
   
    if(this->character->getLanding())
    {
       
        if((this->character->getBody()->GetLinearVelocity().x < 2 && this->character->getBody()->GetLinearVelocity().x >-2))
        {
            this->character->changeState(new CharacterIdleState(this->character));
            return;
        }
    }
    else
    {
        this->character->changeState(new CharacterMidAirState(this->character));
       //CCLOG("%d", this->character->getLanding());
    }
}

bool CharacterMoveState::attack()
{
    this->character->changeState(new CharacterAttackState(this->character));
    return true;
}

bool CharacterMoveState::move()
{
    return true;
}

bool CharacterMoveState::jump()
{
    this->character->changeState(new CharacterJumpState(this->character));
       return true;
}

bool CharacterMoveState::useSkill()
{
    return false;
}
