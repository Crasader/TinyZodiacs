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
#include "Util.h"

USING_NS_CC;

CharacterMoveState::CharacterMoveState(Character* character): CharacterState(character)
{
    
}

bool CharacterMoveState::onEnterState()
{
    if(this->character->runAnimation != NULL)
    {
        CCAnimation* animation = Util::getAnimationFromAnimationObject(this->character->runAnimation);
        if(animation != NULL)
        {
            this->action = CCAnimate::create(animation);
            this->action->retain();
            this->character->getSprite()->runAction(this->action);
        }
    }
    return true;
}

bool CharacterMoveState::onExitState()
{
    stopAction();
    return true;
}

void CharacterMoveState::update(float dt)
{
    
    if(this->character->getLanding() > 0)
    {
        
        if((this->character->getBody()->GetLinearVelocity().x < 3 && this->character->getBody()->GetLinearVelocity().x >-3))
        {
            this->character->changeState(new CharacterIdleState(this->character));
            return;
        }
    }
    else
    {
        this->character->changeState(new CharacterMidAirState(this->character));
        return;
    }
}

bool CharacterMoveState::attack()
{
  
    return true;
}

bool CharacterMoveState::move()
{
    return true;
}

bool CharacterMoveState::jump()
{
    return true;
}

bool CharacterMoveState::useSkill()
{
    return false;
}
