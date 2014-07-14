//
//  CharacterJumpState.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/7/14.
//
//

#include "CharacterJumpState.h"
#include "CharacterMidAirState.h"
#include "Util.h"

USING_NS_CC;

CharacterJumpState::CharacterJumpState(Character* character): CharacterState(character)
{
    
}

bool CharacterJumpState::onEnterState()
{
    //  CCLOG("enter jump state");
    
    
    CCArray* arr = CCArray::create();
    
    CCCallFunc* callBack = CCCallFunc::create(this, callfunc_selector(CharacterJumpState::finishJumpAction));
    
    if(this->character->jumpAnimation != NULL)
    {
        CCAnimation* animation = Util::getAnimationFromAnimationObject(this->character->jumpAnimation);
        if(animation != NULL)
        {
            arr->addObject(CCAnimate::create(animation));
        }
    }
    arr->addObject(callBack);
    
    this->action = CCSequence::create(arr);
    this->action->retain();
    this->character->getSprite()->runAction(this->action);
    
    return true;
}

bool CharacterJumpState::onExitState()
{
    stopAction();
    return true;
}


void CharacterJumpState::update(float dt)
{
    
}

void CharacterJumpState::finishJumpAction()
{
    this->character->changeState(new CharacterMidAirState(this->character));
}

bool CharacterJumpState::attack()
{
    return false;
}

bool CharacterJumpState::move()
{
    return true;
}

bool CharacterJumpState::jump()
{
    return true;
}

bool CharacterJumpState::useSkill()
{
    return false;
}