//
//  CharacterJumpState.cpp
//  SampleCocosProject
//
//  Created by Nguyễn Hòa Phát on 3/7/14.
//
//

#include "CharacterJumpState.h"
#include "CharacterMidAirState.h"

USING_NS_CC;

CharacterJumpState::CharacterJumpState(Character* character): CharacterState(character)
{
    
}


bool CharacterJumpState::onEnterState()
{
    CCAction* jumpAction = CCAnimate::create(this->character->jumpAnimation->getAnimation());
    CCCallFuncND* callBack = CCCallFuncND::create(NULL, callfuncND_selector(CharacterJumpState::finishJumpAction), this->character);
    
    
    CCArray* arr = CCArray::create();
    arr->addObject(jumpAction);
    arr->addObject(callBack);
    
    CCSequence* sequence = CCSequence::create(arr);
    
//    this->character->setAnchorPointForAnimation(this->character->jumpAnimation->getOrigin());
    this->character->getSprite()->runAction(sequence);
    
    return true;
}

bool CharacterJumpState::onExitState()
{
    this->character->getSprite()->stopAllActions();
    return true;
}


void CharacterJumpState::update(float dt)
{
    
}

void CharacterJumpState::finishJumpAction(cocos2d::CCObject* pSender, void* object)
{
    Character* character = (Character*)object;
    character->changeState(new CharacterMidAirState(character));
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
    this->character->changeState(new CharacterJumpState(this->character));
    return false;
}

bool CharacterJumpState::useSkill()
{
    return false;
}