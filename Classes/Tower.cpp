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
#include "GameObjectManager.h"
#include "GB2ShapeCache-x.h"

Tower::Tower()
{
    this->gameObjectID = TOWER;
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
    //    if(this->skill1Animation != NULL)
    //    {
    //        this->skill1Animation->release();
    //    }
    //    if(this->skill2Animation != NULL)
    //    {
    //        this->skill2Animation->release();
    //    }
//    this->body->GetWorld()->DestroyBody(this->sensor);
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
    
//    b2BodyDef bodyDef;
//    bodyDef.bullet=true;
//    bodyDef.type=b2_dynamicBody;
//    bodyDef.fixedRotation=true;
    
    PhysicData* data =  new PhysicData();
    data->BodyId = TOWER_SENSOR;
    data->GameObjectID = TOWER;
    data->FixtureId = TOWER_SENSOR_FIXTURE;
    data->Data = this;
    fixtureDef.userData = data;
    
    this->sensor = this->getBody()->CreateFixture(&fixtureDef);
    
//    this->sensor = this->getBody()->GetWorld()->CreateBody(&bodyDef);
//    this->sensor->CreateFixture(&fixtureDef);
//    this->sensor->SetGravityScale(0);
//    
//    b2RevoluteJointDef revoluteJointDef;
//    revoluteJointDef.bodyA = this->getBody();
//    revoluteJointDef.bodyB = this->sensor;
    
//    this->getBody()->GetWorld()->CreateJoint(&revoluteJointDef);
}

void Tower::setSkin(b2Body *body, CCSprite *sprite)
{
    Character::setSkin(body, sprite);
    this->createSensor();
}

void Tower::setPhysicGroup(uint16 group)
{
    Character::setPhysicGroup(group);
    this->setSensorGroup(group);
}

void Tower::setSensorGroup(uint16 group)
{
//    for (b2Fixture* f = this->sensor->GetFixtureList(); f; f = f->GetNext())
//    {
//        if(f != NULL)
//        {
//            b2Filter filter = f->GetFilterData();
//            filter.categoryBits = group;
//            switch (group) {
//                case GROUP_A:
//                case GROUP_HERO_A:
//                case GROUP_TOWER_A:
//                    filter.maskBits = GROUP_TOWER_B|GROUP_B|GROUP_HERO_B|GROUP_NEUTRUAL|GROUP_TOWER_B;
//                    break;
//                    
//                case GROUP_B:
//                case GROUP_HERO_B:
//                case GROUP_TOWER_B:
//                filter.maskBits = GROUP_TOWER_A|GROUP_A|GROUP_HERO_A|GROUP_NEUTRUAL|GROUP_TOWER_A;
//                    break;
//                    
//                case GROUP_NEUTRUAL:
//                    filter.maskBits = GROUP_A | GROUP_B | GROUP_HERO_A | GROUP_HERO_B;
//                    break;
//                    
//                default:
//                    break;
//            }
//            f->SetFilterData(filter);
//        }
//    }
    
        if(this->sensor != NULL)
        {
            b2Filter filter = this->sensor->GetFilterData();
            filter.categoryBits = group;
            switch (group) {
                case GROUP_A:
                case GROUP_HERO_A:
                case GROUP_TOWER_A:
                    filter.maskBits = GROUP_TOWER_B|GROUP_B|GROUP_HERO_B|GROUP_NEUTRUAL|GROUP_TOWER_B;
                    break;
                    
                case GROUP_B:
                case GROUP_HERO_B:
                case GROUP_TOWER_B:
                    filter.maskBits = GROUP_TOWER_A|GROUP_A|GROUP_HERO_A|GROUP_NEUTRUAL|GROUP_TOWER_A;
                    break;
                    
                case GROUP_NEUTRUAL:
                    filter.maskBits = GROUP_A | GROUP_B | GROUP_HERO_A | GROUP_HERO_B;
                    break;
                    
                default:
                    break;
            }
            this->sensor->SetFilterData(filter);
    }

}

void Tower::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
//    if(data->Data == this)
//    {
        if(holderData->Data == this)
        {
//            PhysicData* physicData = NULL;
//            if(isSideA)
//            {
//                physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//            }
//            else
//            {
//                physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//            }
            
            if(collisionData != NULL)
            {
                if(collisionData->BodyId == CHARACTER_BODY)
                {
                    CCObject* obj = (CCObject*)collisionData->Data;
                    if(this->listTarget->indexOfObject(obj) == CC_INVALID_INDEX)
                    {
                         this->listTarget->addObject(obj);
                    }
                }
            }
        }
//    }
}

void Tower::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(holderData->Data == this)
    {
//        PhysicData* physicData = NULL;
//        if(isSideA)
//        {
//            physicData = (PhysicData*)contact->GetFixtureB()->GetBody()->GetUserData();
//        }
//        else
//        {
//            physicData = (PhysicData*)contact->GetFixtureA()->GetBody()->GetUserData();
//        }
        
        if(collisionData != NULL)
        {
            if(collisionData->BodyId == CHARACTER_BODY)
            {
                this->listTarget->removeObject((CCObject*)collisionData->Data);
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
        
//        if(targetPoint.x < towerPoint.x)
//        {
//            flipDirection(LEFT);
//        }
//        else
//        {
//            flipDirection(RIGHT);
//        }
      //  CCLOG("%0.4f - %0.4f",towerPoint.x,towerPoint.y);
        
        
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
        data.setRotateAngle(atan2(targetPoint.y - towerPoint.y,targetPoint.x - towerPoint.x)-3.14);
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
    //    CCLOG("%f, %f", jointAAnchor.x,jointAAnchor.y);
    return jointAAnchor;
}

void Tower::update(float dt)
{
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
//        this->sensor->SetActive(false);
        
//        GameObjectManager::getInstance()->addObjectRemoved(this);
    }
    
    //
    CCArray* listTargetRemoved = CCArray::create();
    CCObject* object;
    CCARRAY_FOREACH(this->listTarget, object)
    {
        Character* character = (Character*)object;
        
        if(character->isDead())
        {
            listTargetRemoved->addObject(character);
        }
    }
    object = NULL;
    CCARRAY_FOREACH(listTargetRemoved, object)
    {
        this->listTarget->removeObject(object);
    }
    listTargetRemoved->removeAllObjects();
    Character::update(dt);

}

uint16  Tower::getCorrectGroup(Group group)
{
    switch (group)
    {
        case A:
            return GROUP_TOWER_A;
        case B:
            return GROUP_TOWER_B;
        default:
            return GROUP_NEUTRUAL;
    }
}

void Tower::onCreate()
{
    PhysicData* data = new PhysicData();
    data->BodyId = CHARACTER_BODY;
    data->Data = this;
    data->GameObjectID = this->gameObjectID;
    this->getBody()->SetUserData(data);
    Character::onCreate();
}

void Tower::destroy()
{
    Character::destroy();
}

void Tower::attach(Observer* observer)
{
    GameObject::attach(observer);
}

void Tower::detach(Observer* observer)
{
    GameObject::detach(observer);
}

void Tower::notifyToDestroy()
{
    for(int i = 0 ; i < this->listObserver.size() ; i++)
    {
        this->listObserver[i]->notifyToDestroy(this);
    }
}

void Tower::flipDirection(Direction direction)
{
    if(this->direction != direction)
    {
        this->direction = direction;
    }
}

void Tower::setSensor(const char* bodyId)
{
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    PhysicData* data =  new PhysicData();
    data->BodyId = TOWER_SENSOR;
    data->GameObjectID = TOWER;
    data->FixtureId = TOWER_SENSOR_FIXTURE;
    data->Data = this;
    sc->addFixturesToBody(this->body, bodyId, data);
}