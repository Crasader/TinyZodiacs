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

NormalAttack::NormalAttack(GameObject* holder, NormalMeleeSkillData data)
{
    if(holder != NULL)
    {
        this->holder = holder;
        this->data = data;
        
        this->initJointType();
        
        this->createJoint();
        this->data.getskillSensor()->SetActive(false);
        
        //create joint
        
        
        //Set foot sensor bullet
        //        this->data.getskillSensor()->SetBullet(true);
        
        //
        PhysicData* sensorData = new PhysicData();
        sensorData->Id = SKILL_SENSOR;
        sensorData->Data = this;
        this->data.getskillSensor()->SetUserData(sensorData);
        
    }
}

NormalAttack::~NormalAttack()
{
}


void NormalAttack::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInBeginContact(data, contact);
    }
    
}

void NormalAttack::EndContact(b2Contact *contact)
{
    if(contact->GetFixtureA()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact);
    }
    
    if(contact->GetFixtureB()->GetBody()->GetUserData() != NULL)
    {
        PhysicData* data = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        checkCollisionDataInEndContact(data, contact);
    }
}

void NormalAttack::update(float dt)
{
    
}

void NormalAttack::excute()
{
    if(this->getIsExcutable())
    {
        destroyJoint();
        createJoint();
        ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getDelay(), FUCTION_EXCUTE);
        ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getCoolDown(), FUCTION_SET_EXCUTABLE);
        this->isExcutable = false;
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
    this->data.getskillSensor()->SetActive(true);
}

void NormalAttack::stopImmediately()
{
    this->data.getskillSensor()->SetActive(false);
}

void NormalAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact)
{
    if(data->Id == SKILL_SENSOR && data->Data == this)
    {
        CCLOG("Attack collide begin");
    }
}

void NormalAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact)
{
    if(data->Id == SKILL_SENSOR && data->Data == this)
    {
        CCLOG("Attack collide end");
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
    skillJointDef.bodyB = this->data.getskillSensor();
    skillJointDef.collideConnected =false;
    
    JointDef tempA = data.getJointDefA();
    tempA.x = holder_join_type;
    b2Vec2 anchorA = Util::getb2VecAnchor(this->holder->getBody(), tempA);
    skillJointDef.localAnchorA.Set(anchorA.x,anchorA.y);
    
    JointDef tempB = data.getJointDefB();
    tempB.x = this_join_type;
    b2Vec2 anchorB = Util::getb2VecAnchor(this->data.getskillSensor(), tempB);
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

void NormalAttack::setExcuteAble()
{
    this->isExcutable = true;
}