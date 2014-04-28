//
//  Tower.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/21/14.
//
//

#include "Tower.h"
#include "Util.h"
#include "CharacterIdleState.h"
#include "NormalShootingAttack.h"
#include "Util.h"
Tower::Tower()
{
    init();
}

bool Tower::init()
{
    if(!Character::init())
    {
        return false;
    }
    this->sprite = CCSprite::createWithSpriteFrameName("cat_idle_1.png");
    this->listTarget = CCArray::create();
    this->listTarget->retain();
    
    return true;
}

Tower::~Tower()
{
    if(this->skill1Animation != NULL)
    {
        this->skill1Animation->release();
    }
    if(this->skill2Animation != NULL)
    {
        this->skill2Animation->release();
    }
    this->listTarget->release();
}

void Tower::createSensor()
{
    b2CircleShape circleShape;
    circleShape.m_radius = RADIUS_TOWER_SENSOR;
    
    b2FixtureDef fixtureDef;
    fixtureDef.isSensor = true;
    fixtureDef.density = WEIGHTLESS_DENSITY;
    fixtureDef.shape = &circleShape;
    
    b2BodyDef bodyDef;
    bodyDef.bullet=true;
    bodyDef.type=b2_dynamicBody;
    bodyDef.fixedRotation=true;
    
    PhysicData* data =  new PhysicData();
    data->Id = TOWER_SENSOR;
    data->Data = this;
    bodyDef.userData = data;
    
    this->sensor = this->getBody()->GetWorld()->CreateBody(&bodyDef);
    this->sensor->CreateFixture(&fixtureDef);
    this->sensor->SetGravityScale(0);
    
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.bodyA = this->getBody();
    revoluteJointDef.bodyB = this->sensor;
    
    this->getBody()->GetWorld()->CreateJoint(&revoluteJointDef);
}

void Tower::setSkin(b2Body *body, CCSprite *sprite)
{
    Character::setSkin(body, sprite);
    this->createSensor();
}

void Tower::setGroup(uint16 group)
{
    Character::setGroup(group);
    this->setSensorGroup(group);
}

void Tower::setSensorGroup(uint16 group)
{
    for (b2Fixture* f = this->sensor->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL)
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits = group;
            switch (group) {
                case GROUP_A:
                case GROUP_HERO_A:
                    filter.maskBits = GROUP_B|GROUP_HERO_B|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_B:
                case GROUP_HERO_B:
                    filter.maskBits = GROUP_A|GROUP_HERO_A|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_NEUTRUAL:
                    filter.maskBits = GROUP_A | GROUP_B | GROUP_HERO_A | GROUP_HERO_B;
                    break;
                    
                default:
                    break;
            }
            f->SetFilterData(filter);
        }
    }
}

bool Tower::shouldAttack(uint16 enemyGroup)
{
    switch (this->getGroup()) {
        case GROUP_A:
        case GROUP_HERO_A:
            if(this->getGroup() == GROUP_HERO_B || this-> getGroup() == GROUP_B || this->getGroup() == GROUP_NEUTRUAL)
            {
                return true;
            }
            break;
            
        case GROUP_B:
        case GROUP_HERO_B:
            if(this->getGroup() == GROUP_HERO_A || this-> getGroup() == GROUP_A || this->getGroup() == GROUP_NEUTRUAL)
            {
                return true;
            }
            break;
            
        case GROUP_NEUTRUAL:
            if(this->getGroup() == GROUP_HERO_B || this-> getGroup() == GROUP_B || this->getGroup() == GROUP_HERO_A|| this->getGroup() == GROUP_A)
            {
                return true;
            }
            break;
            
        default:
            break;
    }
    return false;
}

void Tower::checkCollisionDataInBeginContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data->Data == this)
    {
        if(data->Data == this)
        {
            PhysicData* physicData = NULL;
            if(isSideA)
            {
                physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
            }
            else
            {
                physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
            }
            
            if(physicData != NULL)
            {
                if(physicData->Id == CHARACTER_BODY)
                {
                    this->listTarget->addObject((CCObject*)physicData->Data);
                }
            }
        }
    }
}

void Tower::checkCollisionDataInEndContact(PhysicData* data, b2Contact *contact, bool isSideA)
{
    if(data->Data == this)
    {
        PhysicData* physicData = NULL;
        if(isSideA)
        {
            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
        }
        else
        {
            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
        }
        
        if(physicData != NULL)
        {
            if(physicData->Id == CHARACTER_BODY)
            {
                this->listTarget->removeObject((CCObject*)physicData->Data);
            }
        }
    }
}

void Tower::aimTarget()
{
    NormalShootingAttack* attack = dynamic_cast<NormalShootingAttack*>(this->normalAttack);
    
    if(attack != NULL)
    {
        b2Vec2 targetPoint = ((Character*)listTarget->objectAtIndex(0))->getPositionInPhysicWorld();
        b2Vec2 towerPoint = getStartPoint(this->body, attack->getData().getJointDefA());
        
        b2Vec2 sp = targetPoint -  towerPoint;
        sp*=TOWER_VELOCITY;
        
//        if(sp.x <0)
//        {
//            flipDirection(LEFT);
//            sp.x = -sp.x;
            //            CCLOG("%lf - %lf",sp.x,sp.y);
//        }
//        else
//        {
//            flipDirection(RIGHT);
            //            CCLOG("%lf - %lf",sp.x,sp.y);
//        }
        
        NormalShootingSkillData data = attack->getData();
        data.setSpeedX(-sp.x);
        data.setSpeedY(sp.y);
        data.setRotateAngle(atan2(targetPoint.y - towerPoint.y,targetPoint.x - towerPoint.x));
        attack->setData(data);
    }
    
    this->attack();
}

b2Vec2 Tower::getStartPoint(b2Body* body, JointDef jointDef)
{
    b2AABB boundingBox = Util::getBodyBoundingBoxDynamic(body);
    
    b2Vec2 jointAAnchor(0,0);
    
    switch (jointDef.x) {
        case JOINT_CENTER:
            jointAAnchor.x = (boundingBox.lowerBound.x+boundingBox.upperBound.x)/2+jointDef.offsetX;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.x = boundingBox.lowerBound.x - jointDef.offsetX;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.x = boundingBox.upperBound.x + jointDef.offsetX;
            break;
        default:
            break;
    }
    
    switch (jointDef.y) {
        case JOINT_CENTER:
            jointAAnchor.y = (boundingBox.lowerBound.y+boundingBox.upperBound.y)/2+jointDef.offsetY;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.y = boundingBox.lowerBound.y - jointDef.offsetY;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.y = boundingBox.upperBound.y + jointDef.offsetY;
            break;
        default:
            break;
    }
//    jointAAnchor += this->getPositionInPhysicWorld();
    CCLOG("%f, %f", jointAAnchor.x,jointAAnchor.y);
    return jointAAnchor;
}

void Tower::update(float dt)
{
    Character::update(dt);
    if(this->characterData.getHealth()>0)
    {
        if(this->listTarget->count() <=0)
        {
            this->changeState(new CharacterIdleState(this));
        }
        else
        {
            this->aimTarget();
        }
    }
    else
    {
        this->body->SetActive(false);
        this->sensor->SetActive(false);
    }
}