//
//  Monster.cpp
//  Headball
//
//  Created by Nhut on 3/13/14.
//
//

#include "Monster.h"
#include "SensorObject.h"
#include "Util.h"
#include "MonsterFactory.h"
#include "GameObjectManager.h"
#include "HealthPointEffect.h"
#include "EffectManager.h"
#include "AnimationEffect.h"

Monster::Monster()
{
    this->gameObjectID = MONSTER;
    isStopMove = false;
    isAttack = false;
    this->landing = 0;
    
    this->listTarget = CCArray::create();
    this->listTarget->retain();
}

Monster::~Monster()
{
    this->listTarget->removeAllObjects();
    this->listTarget->release();
    
    AnimationEffect* effect = AnimationEffect::create();
    effect->setAnimation("effect-smoke");
    EffectManager::getInstance()->runEffect(effect, this->getPositionInPixel());
    
    dropItem();
}

bool Monster::init()
{
    if (!Character::init()) {
        return false;
    }
    this->sprite = CCSprite::createWithSpriteFrameName("cat_idle_1.png");
    return true;
}

void Monster::update(float dt)
{
    if(!isDead())
    {
        this->aimTarget();
    }
    
    if(!isAttack)
    {
        if(!isStopMove)
        {
            this->move(this->direction);
        }
    }
    //
    //remove target
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

void Monster::destroy()
{
    Character::destroy();
}

void Monster::attachSpriteTo(CCNode* node)
{
    GameObject::attachSpriteTo(node);
    node->addChild(this->sprite, CHARACTER_LAYER);
}

void Monster::dropItem()
{
    vector<ItemStruct> listItem = Util::randomItemInList(this->listItem, 1);
    
    for (int i = 0; i < listItem.size(); i++)
    {
        ItemFactory::getInstance()->createItem(listItem[i].itemID.c_str(), this->getPositionInPixel());
    }
}

void Monster::checkCollisionDataInBeginContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    Character::checkCollisionDataInBeginContact(holderData, collisionData, contact);
    
    if(holderData->data == this)
    {
        if(collisionData != NULL)
        {
            //Contact sensor
            if(holderData->fixtureId == MONSTER_SENSOR_FIXTURE && collisionData->fixtureId == BODY_MAIN_FIXTURE && collisionData->data != this)
            {
                if(listTarget->indexOfObject((GameObject*)collisionData->data) == CC_INVALID_INDEX)
                {
                    this->stopMove();
                    this->defaultDirection = this->getDirection();
                    listTarget->addObject((GameObject*)collisionData->data);
                }
                return;
            }
            
            switch (collisionData->bodyId) {
                case MAP_SENSOR:
                {
                    if(holderData->fixtureId == FOOT_SENSOR_FIXTURE)
                    {
                        SensorObject* sensorObject = static_cast<SensorObject*>(collisionData->data);
                        if(sensorObject->checkValidLaneID(this->laneID))
                        {
                            // cung huong
                            if(this->direction == sensorObject->getDirection())
                            {
                                doAction(sensorObject);
                            }
                            else if(sensorObject->getIsBack())
                            {
                                doAction(sensorObject);
                            }
                        }
                    }
                }
                    break;
                    
                case MAP_BASE:
                {
                    if(holderData->fixtureId == BODY_MAIN_FIXTURE)
                    {
                        //                        MapObject* mapObject = static_cast<MapObject*>(collisionData->data);
                        //                        if(!Util::bodiesArePassingThrough(this->body, mapObject->getBody()))
                        //                        {
                        this->isStopMove = false;
                        //                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Monster::checkCollisionDataInEndContact(PhysicData* holderData, PhysicData* collisionData, b2Contact *contact)
{
    Character::checkCollisionDataInEndContact(holderData, collisionData, contact);
    if(holderData->data == this)
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
            //Contact sensor
            if(holderData->fixtureId == MONSTER_SENSOR_FIXTURE && collisionData->fixtureId == BODY_MAIN_FIXTURE && collisionData->data != this)
            {
                listTarget->removeObject((GameObject*)collisionData->data);
                if(listTarget->count()==0)
                {
                    flipDirection(this->defaultDirection);
                }
                return;
            }
            //
            switch (collisionData->bodyId) {
                case MAP_BASE:
                {
                    if(holderData->fixtureId == BODY_MAIN_FIXTURE)
                    {
                        //this->isStopMove = false;
                    }
                    
                }
                    break;
                default:
                    break;
            }
        }
    }
    
}


void Monster::doAction(SensorObject* sensorObject)
{
    if(sensorObject->getMustStop())
    {
        isStopMove = true;
        this->stopMove();
    }
    if(sensorObject->getMoveSpeed() > 0)
    {
        this->move(sensorObject->getDirection(), sensorObject->getMoveSpeed());
    }
    if(sensorObject->getJumpHeight() > 0)
    {
        this->jump(sensorObject->getJumpHeight());
    }
}

void Monster::notifyByAffect(Affect* affect)
{
    Character::notifyByAffect(affect);
}

void Monster::setPhysicGroup(uint16 group)
{
    Character::setPhysicGroup(group);
    this->setSensorGroup(group);
}

void Monster::setSensorGroup(uint16 group)
{
    for (b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext())
    {
        if(f != NULL && ((PhysicData*)(f->GetUserData()))->fixtureId == MONSTER_SENSOR_FIXTURE)
        {
            b2Filter filter = f->GetFilterData();
            filter.categoryBits = GROUP_MONSTER_SENSOR;
            switch (group) {
                case GROUP_A:
                case GROUP_HERO_A:
                case GROUP_TOWER_A:
                    filter.maskBits = GROUP_HERO_B|GROUP_TOWER_B|GROUP_B|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_B:
                case GROUP_HERO_B:
                case GROUP_TOWER_B:
                    filter.maskBits = GROUP_HERO_A|GROUP_TOWER_A|GROUP_A|GROUP_NEUTRUAL;
                    break;
                    
                case GROUP_NEUTRUAL:
                    filter.maskBits = GROUP_A|GROUP_B|GROUP_HERO_A|GROUP_HERO_B|GROUP_TOWER_A|GROUP_TOWER_B;
                    break;
                    
                default:
                    break;
            }
            //            filter.maskBits = 0xFFFFFF;
            f->SetFilterData(filter);
        }
    }
}

void Monster::setSensor(b2Body* sensor)
{
    //    this->sensor=sensor;
    //
    //    PhysicData* data =  new PhysicData();
    //    data->BodyId = MONSTER_SENSOR;
    //    data->Data = this;
    //    data->GameObjectID = MONSTER;
    //    this->sensor->SetUserData(data);
    //
    //    b2RevoluteJointDef revoluteJointDef;
    //    revoluteJointDef.bodyA = this->getBody();
    //    revoluteJointDef.bodyB = this->sensor;
    //
    //    this->getBody()->GetWorld()->CreateJoint(&revoluteJointDef);
}

uint16  Monster::getCorrectGroup(Group group)
{
    switch (group)
    {
        case A:
            return GROUP_A;
        case B:
            return GROUP_B;
        default:
            return GROUP_NEUTRUAL;
    }
}

void Monster::aimTarget()
{
    if(listTarget->count()>0)
    {
        this->isAttack = true;
        
        CCPoint targetPosition = ((GameObject*)listTarget->objectAtIndex(0))->getPositionInPixel();
        if(this->getPositionInPixel().x > targetPosition.x)
        {
            flipDirection(LEFT);
        }
        else
        {
            flipDirection(RIGHT);
        }
        this->attack();
    }
    else
    {
        this->isAttack = false;
    }
}

void Monster::setGroup(Group group)
{
    Character::setGroup(group);
    switch (group)
    {
        case A:
            defaultDirection = RIGHT;
            break;
        case B:
            defaultDirection = LEFT;
            break;
        default:
            defaultDirection = LEFT;
            break;
    }
    flipDirection(defaultDirection);
}

void Monster::onCreate()
{
    Character::onCreate();

    if(this->normalAttack != NULL)
    {
        this->normalAttack->setSkillButtonID(UNKNOWN);
    }
    if(this->skill1 != NULL)
    {
        this->skill1->setSkillButtonID(UNKNOWN);
    }
    if(this->skill2 != NULL)
    {
        this->skill2->setSkillButtonID(UNKNOWN);
    }

}

void Monster::setSensor(const char* bodyId)
{
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    PhysicData* data =  new PhysicData();
    data->bodyId = MONSTER_SENSOR;
    data->fixtureId = MONSTER_SENSOR_FIXTURE;
    data->data = this;
    data->gameObjectID = MONSTER;
    sc->addFixturesToBody(this->body, bodyId, data);
}

void Monster::attach(Observer* observer)
{
    GameObject::attach(observer);
}

void Monster::detach(Observer* observer)
{
    GameObject::detach(observer);
}

void Monster::notifyToDestroy()
{
    GameObject::notifyToDestroy();
}

