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
    //    b2CircleShape circleShape;
    //    circleShape.m_radius = RADIUS_TOWER_SENSOR;
    //
    //    b2FixtureDef fixtureDef;
    //    fixtureDef.isSensor = true;
    //    fixtureDef.density = WEIGHTLESS_DENSITY;
    //    fixtureDef.shape = &circleShape;
    //
    ////    b2BodyDef bodyDef;
    ////    bodyDef.bullet=true;
    ////    bodyDef.type=b2_dynamicBody;
    ////    bodyDef.fixedRotation=true;
    //
    //    PhysicData* data =  new PhysicData();
    //    data->bodyId = TOWER_SENSOR;
    //    data->gameObjectID = TOWER;
    //    data->fixtureId = TOWER_SENSOR_FIXTURE;
    //    data->data = this;
    //    fixtureDef.userData = data;
    //
    //    this->sensor = this->getBody()->CreateFixture(&fixtureDef);
    //
    ////    this->sensor = this->getBody()->GetWorld()->CreateBody(&bodyDef);
    ////    this->sensor->CreateFixture(&fixtureDef);
    ////    this->sensor->SetGravityScale(0);
    ////
    ////    b2RevoluteJointDef revoluteJointDef;
    ////    revoluteJointDef.bodyA = this->getBody();
    ////    revoluteJointDef.bodyB = this->sensor;
    //
    ////    this->getBody()->GetWorld()->CreateJoint(&revoluteJointDef);
}

void Tower::setSkin(b2Body *body, CCSprite *sprite)
{
    Character::setSkin(body, sprite);
}

void Tower::setPhysicGroup(uint16 group)
{
    Character::setPhysicGroup(group);
    this->setSensorGroup(group);
}

void Tower::setSensorGroup(uint16 group)
{
    //          if(this->sensor != NULL)
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
    
    if(holderData->data == this)
    {
        if(collisionData != NULL)
        {
            if(holderData->fixtureId == TOWER_SENSOR_FIXTURE)
            {
                CCObject* obj = (CCObject*)collisionData->data;
                if(this->listTarget->indexOfObject(obj) == CC_INVALID_INDEX)
                {
                    this->listTarget->addObject(obj);
                }
            }
        }
    }
    
}

void Tower::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    if(holderData->data == this)
    {
        if(collisionData != NULL)
        {
            if(holderData->fixtureId == TOWER_SENSOR_FIXTURE)
            {
                this->listTarget->removeObject((CCObject*)collisionData->data);
            }
        }
    }
}

void Tower::aimTarget()
{
    if(this->normalAttack != NULL)
    {
        NormalShootingAttack* attack = dynamic_cast<NormalShootingAttack*>(this->normalAttack);
        
        if(attack != NULL)
        {
            b2Vec2 targetPoint = ((Character*)listTarget->objectAtIndex(0))->getPositionInPhysicWorld();
            b2Vec2 towerPoint = getStartPoint(this->body, attack->getData().getJointDefA());
            
            b2Vec2 sp = targetPoint -  towerPoint;
            sp*=TOWER_VELOCITY;
            NormalShootingSkillData data = attack->getData();
            data.setSpeedX(-sp.x);
            data.setSpeedY(sp.y);
//            data.setRotateAngle(atan2(targetPoint.y - towerPoint.y,targetPoint.x - towerPoint.x)-3.14);
            data.setRotateAngle(0);

            attack->setData(data);
        }
        
        this->attack();
        
    }
}

b2Vec2 Tower::getStartPoint(b2Body* body, JointDef jointDef)
{
    b2AABB boundingBox = Util::getGameObjectBoundingBoxDynamic(this);
    
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
        
        if(character->getIsDead())
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
//            return GROUP_A;
        case B:
            return GROUP_TOWER_B;
//            return GROUP_B;
        default:
            return GROUP_NEUTRUAL;
    }
}

void Tower::onCreate()
{
    PhysicData* data = new PhysicData();
    data->bodyId = CHARACTER_BODY;
    data->data = this;
    data->gameObjectID = this->gameObjectID;
    this->getBody()->SetUserData(data);
    Character::onCreate();
}

void Tower::destroy()
{
    Character::destroy();
}

void Tower::attachSpriteTo(CCNode* node)
{
    GameObject::attachSpriteTo(node);
    node->addChild(this->sprite, UNDER_CHARACTER_LAYER);
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
    data->bodyId = TOWER_SENSOR;
    data->gameObjectID = TOWER;
    data->fixtureId = TOWER_SENSOR_FIXTURE;
    data->data = this;
    sc->addFixturesToBody(this->body, bodyId, data);
    
    this->sensor = Util::getFixtureById(this->body, TOWER_SENSOR_FIXTURE);
}