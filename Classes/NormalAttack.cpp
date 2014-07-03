//
//  NormalAttack.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/17/14.
//
//

#include "NormalAttack.h"
#include "Util.h"
#include "ScheduleManager.h"
#include "LayerIndexConstants.h"
#include "EffectData.h"
#include "Character.h"
#include "Affect.h"

#include "AnimationEffect.h"
#include "EffectManager.h"
#include "GameManager.h"

NormalAttack::NormalAttack(GameObject* holder, NormalMeleeSkillData data): AbstractSkill(holder,data)
{
    this->timeTickAction = NULL;
    this->skillSprite = NULL;
    this->listTarget = NULL;
    if(holder != NULL)
    {
        this->data = data;
    }
    shouldDeactiveSensor = false;
}

NormalAttack::~NormalAttack()
{
    stopImmediately();
    if(GameManager::getInstance()->getGameplayHolder().worldHolder != NULL)
    {
        data.getSkillSensor()->SetActive(false);
        data.getSkillSensor()->GetWorld()->DestroyBody(data.getSkillSensor());
    }
    
    if(this->skillSprite != NULL)
    {
        this->skillSprite->removeFromParent();
        this->skillSprite->stopAllActions();
        this->skillSprite->release();
    }
    
    this->data.releaseEffectLists();
}

void NormalAttack::onCreate()
{
    this->initJointType();
    this->createJoint();
    this->data.getSkillSensor()->SetActive(false);
    this->data.getSkillSensor()->SetBullet(false);
    this->data.getSkillSensor()->SetGravityScale(0);
    for (b2Fixture* f = this->data.getSkillSensor()->GetFixtureList(); f; f = f->GetNext())
    {
        PhysicData* sensorData = new PhysicData();
        sensorData->bodyId = SKILL_SENSOR;
        sensorData->gameObjectID = SKILL_OBJECT;
        sensorData->fixtureId = SKILL_FIXTURE;
        sensorData->data = this;
        
        f->SetUserData(sensorData);
    }
    //this->data.getSkillSensor()->SetUserData(sensorData);
    
    if(this->data.getSkillAnimationData().haveAnyData() == true)
    {
        this->skillSprite = CCSprite::create();
        this->skillSprite->retain();
    }
    
    if(data.getApplyType() == APPLY_OVERTIME)
    {
        this->listTarget = CCArray::create();
        this->listTarget->retain();
    }
    else
    {
        this->listTarget = NULL;
    }
    
}

void NormalAttack::destroy()
{
    //remove target
    if(this->listTarget != NULL)
    {
        CCObject* object = NULL;
        CCARRAY_FOREACH(this->listTarget, object)
        {
            Character* gameObject = static_cast<Character*>(object);
            gameObject->detach(this);
        }
        this->listTarget->removeAllObjects();
    }

    AbstractSkill::destroy();
}

void NormalAttack::update(float dt)
{
    if(this->skillSprite != NULL)
    {
        CCPoint bodyPosition = ccp(this->data.getSkillSensor()->GetPosition().x*PTM_RATIO,this->data.getSkillSensor()->GetPosition().y*PTM_RATIO);
        this->skillSprite->setPosition(bodyPosition);
        this->skillSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->data.getSkillSensor()->GetAngle()));
    }
    
    if(this->skillButtonID != UNKNOWN);
    {
        if(this->isExcutable)
        {
        }
        else
        {
            StateCommandData *data = new StateCommandData();
            data->controllerId = this->skillButtonID;
            data->isActive = false;
            this->holder->notifyUIChange(data);
        }
    }
}

void NormalAttack::excute()
{
    if(this->isDisable == false && this->getIsExcutable())
    {
        destroyJoint();
        createJoint();
        this->data.getSkillSensor()->SetActive(true);
        //
        if(this->excuteAction != NULL)
        {
            this->excuteAction->stop();
            this->excuteAction->release();
        }
        CCCallFunc* excuteFunc = CCCallFunc::create(this, callfunc_selector(NormalAttack::excuteImmediately));
        this->excuteAction =  ScheduleManager::getInstance()->scheduleFuction(excuteFunc, this->data.getDelay());
        this->excuteAction->retain();
        
        //
        if(this->data.getCoolDown() > 0)
        {
            if(this->coolDownAction != NULL)
            {
                this->coolDownAction->stop();
                this->coolDownAction->release();
            }
            CCCallFunc* coolDownFunc = CCCallFunc::create(this, callfunc_selector(NormalAttack::setExcuteAble));
            this->coolDownAction = ScheduleManager::getInstance()->scheduleFuction(coolDownFunc, this->data.getCoolDown());
            this->coolDownAction->retain();
            
            this->isExcutable = false;
            
            if(this-> skillButtonID != UNKNOWN)
            {
                StateCommandData *data = new StateCommandData();
                data->controllerId = this->skillButtonID;
                data->isActive = false;
                this->holder->notifyUIChange(data);
            }
        }
        //
        changeState(PRE_EXCUTE);
    }
}

void NormalAttack::stop()
{
    changeState(PRE_STOP);
}

void NormalAttack::excuteImmediately()
{
    if(isDisable)
    {
        return;
    }
    //small trick to recall begin contact
    this->data.getSkillSensor()->SetActive(false);
    this->data.getSkillSensor()->SetActive(true);
    
    //start life time
    if(this->stopAction != NULL)
    {
        if(this->stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(stopAction);
        }
        this->stopAction->release();
    }
    CCCallFunc* stopFunc = CCCallFunc::create(this, callfunc_selector(NormalAttack::stopImmediately));
    
    this->stopAction = ScheduleManager::getInstance()->scheduleFunction(stopFunc, NULL, this->data.getLifeTime(), 1);
    this->stopAction->retain();
    //start time tick action
    if(data.getApplyType() == APPLY_OVERTIME)
    {
        CCCallFunc* timeTick = CCCallFunc::create(this, callfunc_selector(NormalAttack::applyEffectOnTimeTick));
        this->timeTickAction = ScheduleManager::getInstance()->scheduleFunctionForever(timeTick, NULL, this->data.getTimeTick());
        this->timeTickAction->retain();
    }
    //play sound
    changeState(EXCUTE);
}

void NormalAttack::stopImmediately()
{
    if(isDisable)
    {
        return;
    }
    changeState(STOP);

    //deactive sensor
    this->data.getSkillSensor()->SetActive(false);
    if(this->skillSprite !=NULL)
    {
        this->skillSprite->stopAllActions();
        this->skillSprite->removeFromParent();
    }
    //stop time tick
    if(this->timeTickAction != NULL)
    {
        if(this->timeTickAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(this->timeTickAction);
        }
        this->timeTickAction->release();
        this->timeTickAction = NULL;
    }
    // stop life time
    if(this->stopAction != NULL)
    {
        if(this->stopAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(stopAction);
        }
        this->stopAction->release();
        this->stopAction = NULL;
    }
    //stop excuteaction - happen when stop skill before excuteimidietly
    if(this->excuteAction != NULL)
    {
        if(this->excuteAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(excuteAction);
        }
        this->excuteAction->release();
        this->excuteAction = NULL;
    }
    //remove target
    if(this->listTarget != NULL)
    {
        CCObject* object = NULL;
        CCARRAY_FOREACH(this->listTarget, object)
        {
            Character* gameObject = static_cast<Character*>(object);
            gameObject->detach(this);
        }
        this->listTarget->removeAllObjects();
    }
    //
}

void NormalAttack::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    
    if(this->isDisable)
    {
        return;
    }
    
    
    if(holderData->bodyId == SKILL_SENSOR && holderData->data == this )
        
    {
        if(collisionData != NULL)
        {
            switch (collisionData->bodyId) {
                case CHARACTER_BODY:
                {
                    if(this->currentState == EXCUTE)
                    {
                        Character* character = (Character*)collisionData->data;
                        //                        if(character != holder)
                        {
                            if(listTarget != NULL)
                            {
                                listTarget->addObject(character);
                                character->attach(this);
                            }
                            //play sound
                            playSoundByState(HIT, this->data.getSoundData());
                            //
                            NormalMeleeSkillData calculatedSkillData = this->data;
                            calculateSkillData(&calculatedSkillData, ((Character*)this->holder)->getcharacterData());
                            
                            if(character != holder)
                            {
                                if(character->getGroup() == this->holder->getGroup())
                                {
                                    Util::applyEffectFromList(calculatedSkillData.getListAlliesEffect(), character);
                                }
                                else
                                {
                                    Util::applyEffectFromList(calculatedSkillData.getListEnemyEffect(), character);
                                }
                            }
                            else
                            {
                                Util::applyEffectFromList(calculatedSkillData.getlistSelfEffect(), character);
                            }
                        }
                        
                    }
                    
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void NormalAttack::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(this->isDisable)
    {
        return;
    }
    
    if(holderData->bodyId == SKILL_SENSOR && holderData->data == this)
    {
        if(collisionData != NULL)
        {
            switch (collisionData->bodyId) {
                case CHARACTER_BODY:
                {
                    Character* character = (Character*)collisionData->data;
                    
                    if(listTarget != NULL)
                    {
                        if(this->listTarget->indexOfObject(character) != CC_INVALID_INDEX )
                        {
                            character->detach(this);
                            listTarget->removeObject(character);
                        }
                    }
                }
                default:
                    break;
            }
        }
    }
}

void NormalAttack::destroyJoint()
{
    if(this->skillJoint != NULL && this->holder->getBody()->GetWorld()->IsLocked() == false)
    {
        this->holder->getBody()->GetWorld()->DestroyJoint(this->skillJoint);
        this->skillJoint = NULL;
    }
}

void NormalAttack::createJoint()
{
    if(this->holder->getBody()->GetWorld()->IsLocked() == false)
    {
        if(this->data.getJointDefA().x == JOINT_REAR)
        {
            if(this->holder->getDirection() == LEFT)
            {
                this->holder_join_type = JOINT_BOTTOM_OR_LEFT;
            }
            else
            {
                this->holder_join_type = JOINT_TOP_OR_RIGHT;
            }
            if(this->data.getJointDefB().x == JOINT_REAR)
            {
                this->this_join_type = -this->holder_join_type;
            }
        }
        
        //create joint
        b2RevoluteJointDef skillJointDef;
        skillJointDef.bodyA = this->holder->getBody();
        skillJointDef.bodyB = this->data.getSkillSensor();
        skillJointDef.collideConnected =false;
        
        JointDef tempA = data.getJointDefA();
        tempA.x = holder_join_type;
        b2AABB aabb = Util::getGameObjectBoundingBox(this->holder);
        b2Vec2 anchorA = Util::getb2VecAnchor(aabb, tempA);
        
        skillJointDef.localAnchorA.Set(anchorA.x,anchorA.y);
        
        JointDef tempB = data.getJointDefB();
        tempB.x = this_join_type;
        b2Vec2 anchorB = Util::getb2VecAnchor(this->data.getSkillSensor(), tempB);
        skillJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
        
        skillJointDef.collideConnected =true;
        
        this->skillJoint=this->holder->getBody()->GetWorld()->CreateJoint(&skillJointDef);
    }
}

void NormalAttack::initJointType()
{
    this->holder_join_type = this->data.getJointDefA().x;
    this->this_join_type = this->data.getJointDefB().x;
    
    if(this->data.getJointDefA().x == JOINT_REAR)
    {
        if(this->holder->getDirection() == LEFT)
        {
            this->holder_join_type = JOINT_BOTTOM_OR_LEFT;
        }
        else
        {
            this->holder_join_type = JOINT_TOP_OR_RIGHT;
        }
        if(this->data.getJointDefB().x == JOINT_REAR)
        {
            this->this_join_type = -this->holder_join_type;
        }
    }
}

void NormalAttack::setPhysicGroup(uint16 group)
{
    for (b2Fixture* f = this->data.getSkillSensor()->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            Util::setFixtureGroup(f, group);
        }
    }
}

void NormalAttack::setExcuteAble()
{
    if(isDisable)
    {
        return;
    }
    this->isExcutable = true;
    
    if(this->skillButtonID != UNKNOWN)
    {
        StateCommandData *data = new StateCommandData();
        data->controllerId = this->skillButtonID;
        data->isActive = true;
        this->holder->notifyUIChange(data);
    }
}

void NormalAttack::stopAllAction()
{
    AbstractSkill::stopAllAction();
    
    if(timeTickAction != NULL)
    {
        if(timeTickAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(timeTickAction);
        }
        timeTickAction->release();
        timeTickAction = NULL;
    }
}

void NormalAttack::applyEffectOnTimeTick()
{
    if(isDisable)
    {
        return;
    }
    CCObject* obj = NULL;
    CCARRAY_FOREACH(listTarget, obj)
    {
        Character* character = (Character*)obj;
        
        NormalMeleeSkillData calculatedSkillData = this->data;
        calculateSkillData(&calculatedSkillData, ((Character*)this->holder)->getcharacterData());
        
        if(this->holder != character)
        {
            if(character->getGroup() == this->holder->getGroup())
            {
                Util::applyEffectFromList(calculatedSkillData.getListAlliesEffect(), character);
            }
            else
            {
                Util::applyEffectFromList(calculatedSkillData.getListEnemyEffect(), character);
            }
        }
        else
        {
            Util::applyEffectFromList(calculatedSkillData.getlistSelfEffect(), character);
        }
    }
}

void NormalAttack::notifyToDestroy(GameObject* object)
{
    if(this->listTarget != NULL)
    {
        if(this->listTarget->indexOfObject(object) != CC_INVALID_INDEX)
        {
            this->listTarget->removeObject(object);
        }
    }
}

void NormalAttack::playAnimationByState(SkillState state)
{
    switch (state) {
        case PRE_EXCUTE:
        {
            AnimationObject* animationObj = this->data.getSkillAnimationData().getPreExcuteAnimation();
            if(animationObj != NULL && this->holder != NULL && this->holder->getSprite() != NULL)
            {
                this->skillSprite->removeFromParent();
                this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
                CCAnimate* action = CCAnimate::create(animationObj->getAnimation());
                this->skillSprite->runAction(action);
                this->skillSprite->setPosition(ccp(0,0));
            }
        }
            break;
        case EXCUTE:
        {
            AnimationObject* animationObj = this->data.getSkillAnimationData().getExcuteAnimation();
            if(animationObj != NULL && this->holder != NULL && this->holder->getSprite() != NULL)
            {
                this->skillSprite->removeFromParent();
                this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
                CCAnimate* action = CCAnimate::create(animationObj->getAnimation());
                this->skillSprite->runAction(action);
                this->skillSprite->setPosition(ccp(0,0));
            }
        }
            break;
        case PRE_STOP:
        {
            AnimationObject* animationObj = this->data.getSkillAnimationData().getPreStopAnimation();
            if(animationObj != NULL && this->holder != NULL && this->holder->getSprite() != NULL)
            {
                this->skillSprite->removeFromParent();
                this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
                CCAnimate* action = CCAnimate::create(animationObj->getAnimation());
                this->skillSprite->runAction(action);
                this->skillSprite->setPosition(ccp(0,0));
            }
        }
            break;
        case STOP:
        {
            AnimationObject* animationObj = this->data.getSkillAnimationData().getStopAnimation();
            if(animationObj != NULL && this->holder != NULL && this->holder->getSprite() != NULL)
            {
                this->skillSprite->removeFromParent();
                this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
                CCAnimate* action = CCAnimate::create(animationObj->getAnimation());
                this->skillSprite->runAction(action);
                this->skillSprite->setPosition(ccp(0,0));
            }
        }
            break;
        default:
            break;
    }
}

void NormalAttack::changeState(SkillState state)
{
    this->currentState = state;
    switch (state) {
        case PRE_EXCUTE:
        {
            playSoundByState(PRE_EXCUTE, this->getData().getSoundData());
            playAnimationByState(PRE_EXCUTE);
        }
            break;
        case EXCUTE:
        {
            playSoundByState(EXCUTE, this->getData().getSoundData());
            playAnimationByState(EXCUTE);
        }
            break;
        case PRE_STOP:
        {
            playSoundByState(PRE_STOP, this->getData().getSoundData());
            playAnimationByState(PRE_STOP);
        }
            break;
        case STOP:
        {
            playSoundByState(STOP, this->getData().getSoundData());
            playAnimationByState(STOP);
        }
            break;
        default:
            break;
    }
    
}