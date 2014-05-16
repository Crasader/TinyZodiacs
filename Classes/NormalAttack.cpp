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
#include "Effect.h"

NormalAttack::NormalAttack(GameObject* holder, NormalMeleeSkillData data): AbstractSkill(holder,data)
{
    this->skillSprite = NULL;
    if(holder != NULL)
    {
        this->data = data;
    }
}

NormalAttack::~NormalAttack()
{
    stopImmediately();
    CC_SAFE_RELEASE(this->skillSprite);
    data.getSkillSensor()->SetActive(false);
    data.getSkillSensor()->GetWorld()->DestroyBody(data.getSkillSensor());
    
//    if(listTarget != NULL)
//    {
//        listTarget->removeAllObjects();
//        listTarget->release();
//    }
    this->data.releaseEffectLists();
}

void NormalAttack::onCreate()
{
    this->initJointType();
    
    this->createJoint();
    this->data.getSkillSensor()->SetActive(false);
    this->data.getSkillSensor()->SetBullet(true);

    PhysicData* sensorData = new PhysicData();
    sensorData->Id = SKILL_SENSOR;
    sensorData->GameObjectID = SKILL_OBJECT;
    sensorData->Data = this;
    this->data.getSkillSensor()->SetUserData(sensorData);

    if(this->data.getSkillAnimation() != NULL && this->data.getSkillAnimation()->getAnimation() != NULL)
    {
        this->skillSprite = CCSprite::create();
        this->skillSprite->retain();
        this->data.getSkillAnimation()->getAnimation()->setLoops(INFINITY);
    }

}

void NormalAttack::destroy()
{
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
    
    if(this->holderButton != NULL)
    {
        if(this->isExcutable)
        {
            //            this->holderButton->changeState(ENABLE);
        }
        else
        {
            this->holderButton->changeState(DISABLE);
        }
    }
}

void NormalAttack::excute()
{
    if(this->getIsExcutable())
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
            if(this-> holderButton != NULL)
            {
                this->holderButton->changeState(DISABLE);
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
    this->data.getSkillSensor()->SetActive(true);
    if(this->data.getSkillAnimation() != NULL && this->holder != NULL)
    {
        this->skillSprite->removeFromParent();
        this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
        CCAnimate* action = CCAnimate::create(this->data.getSkillAnimation()->getAnimation());
        this->skillSprite->runAction(action);
        this->skillSprite->setPosition(ccp(0,0));
    }
}

void NormalAttack::stopImmediately()
{
    this->data.getSkillSensor()->SetActive(false);
    if(this->data.getSkillAnimation() != NULL && this->holder != NULL)
    {
        this->skillSprite->stopAllActions();
        this->skillSprite->removeFromParent();
    }
}

void NormalAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(this->isDisable)
    {
     return;
    }
    if(data->Id == SKILL_SENSOR && data->Data == this )
    {
        PhysicData* otherData;
        if(isSideA)
        {
            otherData = (PhysicData* )contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            otherData = (PhysicData* )contact->GetFixtureA()->GetBody()->GetUserData();
        }
        if(otherData != NULL)
        {
            switch (otherData->Id) {
                case CHARACTER_BODY:
                {
                    Character* character = (Character*)otherData->Data;
                    //                    if(character != holder)
                    //                    {
                    

                        NormalMeleeSkillData calculatedSkillData = this->data;
                        calculateSkillData(&calculatedSkillData, this->holder);
                        
                        if(character->getGroup() == this->holder->getGroup())
                        {
                            // CCLOG("Allie begin");
                        }
                        else
                        {
                            // CCLOG("Enemy begin");
                            for(int i=0 ; i<calculatedSkillData.getListEnemyEffect().size() ; i++)
                            {
                                Effect* effect = new Effect(calculatedSkillData.getListEnemyEffect()[i], character);
                                character->applyEffect(effect);
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

void NormalAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(this->isDisable)
    {
        return;
    }
    if(data->Id == SKILL_SENSOR && data->Data == this)
    {
        PhysicData* otherData;
        if(isSideA)
        {
            otherData = (PhysicData* )contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            otherData = (PhysicData* )contact->GetFixtureA()->GetBody()->GetUserData();
        }
        
        if(otherData != NULL)
        {
            switch (otherData->Id) {
                case CHARACTER_BODY:
                {
                    Character* character = (Character*)otherData->Data;
                    if(character != holder)
                    {
                 
                        //                        if(character->getGroup() == this->holder->getGroup())
                        //                        {
                        //                            // CCLOG("Allie end");
                        //                        }
                        //                        else
                        //                        {
                        //                            //  CCLOG("Enemy end");
                        //                        }
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
        b2Vec2 anchorA = Util::getb2VecAnchor(this->holder->getBody(), tempA);
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
    this->isExcutable = true;
    if(this->holderButton != NULL && this->holderButton->getState() == DISABLE)
    {
        this->holderButton->changeState(ENABLE);
    }
    
    //    this->coolDownAction->release();
    //    this->coolDownAction = NULL;
}