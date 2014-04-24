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

NormalAttack::NormalAttack(GameObject* holder, NormalMeleeSkillData data)
{
    if(holder != NULL)
    {
        this->holder = holder;
        this->data = data;
        this->holderButton = NULL;
        
        this->initJointType();
        
        this->createJoint();
        this->data.getSkillSensor()->SetActive(false);
        
        this->data.getSkillSensor()->SetBullet(true);
        
        this->isExcutable = true;
        
        //
        PhysicData* sensorData = new PhysicData();
        sensorData->Id = SKILL_SENSOR;
        sensorData->Data = this;
        this->data.getSkillSensor()->SetUserData(sensorData);
        
        //
        this->skillSprite = NULL;
        if(this->data.getSkillAnimation() != NULL && this->data.getSkillAnimation()->getAnimation() != NULL)
        {
            this->skillSprite = CCSprite::create("Default.png");
            this->skillSprite->retain();
            this->data.getSkillAnimation()->getAnimation()->setLoops(INFINITY);
        }
        
    }
}

NormalAttack::~NormalAttack()
{
    this->skillSprite->release();
}


void NormalAttack::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact, false);
    }
    
}

void NormalAttack::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, true);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact, false);
    }
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
        ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getDelay(), FUCTION_EXCUTE);
        if(this->data.getCoolDown() > 0)
        {
            ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getCoolDown(), FUCTION_SET_EXCUTABLE);
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
    if(this->data.getLifeTime() >=0)
    {
        ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getLifeTime(), FUCTION_STOP);
    }
    else
    {
        this->stopImmediately();
    }
}

void NormalAttack::excuteImmediately()
{
    //    this->destroyJoint();
    this->data.getSkillSensor()->SetActive(true);
    if(this->data.getSkillAnimation() != NULL)
    {
        this->holder->getSprite()->getParent()->addChild(this->skillSprite, this->data.getAnimationLayerIndex());
        CCAnimate* action = CCAnimate::create(this->data.getSkillAnimation()->getAnimation());
        this->skillSprite->runAction(action);
        this->skillSprite->setPosition(ccp(0,0));
    }
}

void NormalAttack::stopImmediately()
{
    this->data.getSkillSensor()->SetActive(false);
    if(this->data.getSkillAnimation() != NULL)
    {
        this->skillSprite->stopAllActions();
        this->holder->getSprite()->getParent()->removeChild(this->skillSprite);
    }
}

void NormalAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
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
                    if(this->holder != otherData->Data)
                    {
                        CCLOG("Attack collide begin");
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
                    if(this->holder != otherData->Data)
                    {
                        CCLOG("Attack collide end");
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void NormalAttack::destroyJoint()
{
    if(this->skillJoint != NULL)
    {
        this->holder->getBody()->GetWorld()->DestroyJoint(this->skillJoint);
        this->skillJoint = NULL;
    }
}

void NormalAttack::createJoint()
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

void NormalAttack::setGroup(int group)
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
}