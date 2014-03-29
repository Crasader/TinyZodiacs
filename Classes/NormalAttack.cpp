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
        
//        this->data.getskillSensor()->SetActive(false);
        
        //create joint
        skillJoint.bodyA = this->holder->getBody();
        skillJoint.bodyB = this->data.getskillSensor();
        skillJoint.collideConnected =true;
        
        JointDef tempA = data.getJointDefA();
        holder_join_type = JOINT_BOTTOM_OR_LEFT;
        tempA.x = holder_join_type;
        b2Vec2 anchorA = Util::getb2VecAnchor(this->holder->getBody(), tempA);
        skillJoint.localAnchorA.Set(anchorA.x,anchorA.y);
        
        JointDef tempB = data.getJointDefB();
        this_join_type = JOINT_TOP_OR_RIGHT;
        tempB.x = this_join_type;
        b2Vec2 anchorB = Util::getb2VecAnchor(this->data.getskillSensor(), tempB);
        skillJoint.localAnchorB.Set(anchorB.x, anchorB.y);

        //Set foot sensor bullet
//        this->data.getskillSensor()->SetBullet(true);
        
        //
        PhysicData* sensorData = new PhysicData();
        sensorData->Id = SKILL_SENSOR;
        sensorData->Data = this;
        this->data.getskillSensor()->SetUserData(sensorData);
        
        this->holder->getBody()->GetWorld()->CreateJoint(&skillJoint);
    }
}

NormalAttack::~NormalAttack()
{
    ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getDelay());
}

void NormalAttack::BeginContact(b2Contact *contact)
{
    CCLOG("Attack begin");
}

void NormalAttack::EndContact(b2Contact *contact)
{
    CCLOG("Attack end");
}

void NormalAttack::update(float dt)
{
    
}

void NormalAttack::excute()
{
    ScheduleManager::getInstance()->scheduleForSkill(this, this->data.getDelay());
}

void NormalAttack::stop()
{
    this->data.getskillSensor()->SetActive(false);
}

void NormalAttack::excuteImmediately()
{
    if((holder->getDirection() == LEFT && holder_join_type != JOINT_BOTTOM_OR_LEFT) || (holder->getDirection() == RIGHT && holder_join_type != JOINT_TOP_OR_RIGHT))
    {
        flip();
    }
    
    this->data.getskillSensor()->SetActive(true);
}


void NormalAttack::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact)
{
    
}

void NormalAttack::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact)
{
    
}

void NormalAttack::flip()
{
    JointDef tempA = data.getJointDefA();
    holder_join_type = -holder_join_type;
    tempA.x = holder_join_type;
    skillJoint.localAnchorA = Util::getb2VecAnchor(this->holder->getBody(), tempA);
    
//    JointDef tempB = data.getJointDefB();
//    this_join_type = -this_join_type;
//    tempB.x = this_join_type;
//    skillJoint.localAnchorB = Util::getb2VecAnchor(this->data.getskillSensor(), tempB);
}
