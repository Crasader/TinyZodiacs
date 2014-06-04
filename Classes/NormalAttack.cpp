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
}

NormalAttack::~NormalAttack()
{
    if(GameManager::getInstance()->getGameplayHolder().worldHolder != NULL)
    {
        data.getSkillSensor()->SetActive(false);
        data.getSkillSensor()->GetWorld()->DestroyBody(data.getSkillSensor());
    }
    CC_SAFE_RELEASE(this->skillSprite);
    
    this->data.releaseEffectLists();
}

void NormalAttack::onCreate()
{
    this->initJointType();
    
    this->createJoint();
    this->data.getSkillSensor()->SetActive(false);
    this->data.getSkillSensor()->SetBullet(true);
    
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
    
    if(this->data.getSkillAnimation() != NULL && this->data.getSkillAnimation()->getAnimation() != NULL)
    {
        this->skillSprite = CCSprite::create();
        this->skillSprite->retain();
//        this->data.getSkillAnimation()->getAnimation()->setLoops(INFINITY);
    }
    
    if(data.getLifeTime() > 0 && data.getTimeTick() > 0)
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
    stopImmediately();
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
            //            data->isActive = true;
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
        
        if(this->excuteAction != NULL)
        {
            this->excuteAction->stop();
            this->excuteAction->release();
        }
        CCCallFunc* excuteFunc = CCCallFunc::create(this, callfunc_selector(NormalAttack::excuteImmediately));
        this->excuteAction =  ScheduleManager::getInstance()->scheduleFuction(excuteFunc, this->data.getDelay());
        this->excuteAction->retain();
        
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
    }
}

void NormalAttack::stop()
{
    if(this->stopAction != NULL)
    {
        
        ScheduleManager::getInstance()->stopAction(stopAction);
        this->stopAction->release();
    }
    CCCallFunc* stopFunc = CCCallFunc::create(this, callfunc_selector(NormalAttack::stopImmediately));
    
    this->stopAction = ScheduleManager::getInstance()->scheduleFunction(stopFunc, NULL, this->data.getLifeTime(), 1);
    this->stopAction->retain();
}

void NormalAttack::excuteImmediately()
{
    if(isDisable)
    {
        return;
    }
    
    this->data.getSkillSensor()->SetActive(true);
    if(this->data.getSkillAnimation() != NULL && this->holder != NULL && this->holder->getSprite() != NULL)
    {
        this->skillSprite->removeFromParent();
        this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
        CCAnimate* action = CCAnimate::create(this->data.getSkillAnimation()->getAnimation());
        this->skillSprite->runAction(action);
        this->skillSprite->setPosition(ccp(0,0));
    }
    //start time tick action
    if(data.getLifeTime() >0 && data.getTimeTick() >0)
    {
        CCCallFunc* timeTick = CCCallFunc::create(this, callfunc_selector(NormalAttack::applyEffectOnTimeTick));
        this->timeTickAction = ScheduleManager::getInstance()->scheduleFunctionForever(timeTick, NULL, this->data.getTimeTick());
        this->timeTickAction->retain();
    }
}

void NormalAttack::stopImmediately()
{
    if(isDisable)
    {
        return;
    }
   
    //deactive sensor
    this->data.getSkillSensor()->SetActive(false);
    if(this->data.getSkillAnimation() != NULL && this->holder != NULL)
    {
        this->skillSprite->stopAllActions();
        this->skillSprite->removeFromParent();
    }
    //stop time tick
    if(this->timeTickAction != NULL)
    {
        //            this->timeTickAction->stop();
        if(this->timeTickAction->isDone() == false)
        {
            ScheduleManager::getInstance()->stopAction(this->timeTickAction);
        }
        this->timeTickAction->release();
        this->timeTickAction = NULL;
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
                    //   if(otherData->GameObjectID == HERO)
                    {
                        Character* character = (Character*)collisionData->data;
                        if(character != holder)
                        {
                            if(listTarget != NULL)
                            {
                                listTarget->addObject(character);
                                character->attach(this);
                            }
                            
                            NormalMeleeSkillData calculatedSkillData = this->data;
                            calculateSkillData(&calculatedSkillData, ((Character*)this->holder)->getcharacterData());
                            
                            if(character->getGroup() == this->holder->getGroup())
                            {
                                Util::applyEffectFromList(calculatedSkillData.getListAlliesEffect(), character);
                            }
                            else
                            {
                                Util::applyEffectFromList(calculatedSkillData.getListEnemyEffect(), character);
                            }
                            
//                            b2WorldManifold worldManifold;
//                            contact->GetWorldManifold(&worldManifold);
//                            
//                            //now you can use these properties for whatever you need
//                            b2Vec2 contactPoint = (worldManifold.points[0]); //b2Vec2
//                            AnimationEffect* effect = AnimationEffect::create();
//                            effect->setAnimation("effect-smoke");
//                            EffectManager::getInstance()->runEffect(effect, CCPoint(contactPoint.x/32, contactPoint.y/32));

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
//        b2Vec2 anchorA = Util::getb2VecAnchor(this->holder->getBody(), tempA);
        b2Fixture* mainFix = Util::getFixtureById(this->holder->getBody(), BODY_MAIN_FIXTURE);
        b2Vec2 anchorA = Util::getb2VecAnchor(mainFix, tempA);
        skillJointDef.localAnchorA.Set(anchorA.x,anchorA.y);
        
        JointDef tempB = data.getJointDefB();
        tempB.x = this_join_type;
        b2Vec2 anchorB = Util::getb2VecAnchor(this->data.getSkillSensor(), tempB);
        skillJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
        
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
        
        if(character->getGroup() == this->holder->getGroup())
        {
            Util::applyEffectFromList(calculatedSkillData.getListAlliesEffect(), character);
        }
        else
        {
            Util::applyEffectFromList(calculatedSkillData.getListEnemyEffect(), character);
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