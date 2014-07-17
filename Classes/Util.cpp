//
//  Util.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#include "Util.h"
#include "Character.h"
#include "Affect.h"

b2AABB Util::getBodyBoundingBox(b2Body* body)
{
    if(body != NULL)
    {
        //Calculate b
        b2AABB aabb;
        
        b2Transform t;
        t.SetIdentity();
        
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = body->GetFixtureList();
        while (fixture != NULL)
        {
            //            aabb.Combine(aabb, fixture->GetAABB(0));
            //            fixture = fixture->GetNext();
            const b2Shape *shape = fixture->GetShape();
            const int childCount = shape->GetChildCount();
            for (int child = 0; child < childCount; ++child) {
                const b2Vec2 r(shape->m_radius, shape->m_radius);
                b2AABB shapeAABB;
                shape->ComputeAABB(&shapeAABB, t, child);
                shapeAABB.lowerBound = shapeAABB.lowerBound + r;
                shapeAABB.upperBound = shapeAABB.upperBound - r;
                aabb.Combine(shapeAABB);
            }
            fixture = fixture->GetNext();
        }
        return aabb;
    }
    return b2AABB();
}

b2AABB Util::getFixtureBoundingBox(b2Fixture* fixture)
{
    if(fixture != NULL)
    {
        //Calculate b
        b2AABB aabb;
        
        b2Transform t;
        t.SetIdentity();
        
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        
        const b2Shape *shape = fixture->GetShape();
        const int childCount = shape->GetChildCount();
        for (int child = 0; child < childCount; ++child) {
            const b2Vec2 r(shape->m_radius, shape->m_radius);
            b2AABB shapeAABB;
            shape->ComputeAABB(&shapeAABB, t, child);
            shapeAABB.lowerBound = shapeAABB.lowerBound + r;
            shapeAABB.upperBound = shapeAABB.upperBound - r;
            aabb.Combine(shapeAABB);
        }
        fixture = fixture->GetNext();
        return aabb;
    }
    return b2AABB();
}


b2AABB Util::getBodyBoundingBoxDynamic(b2Body* body)
{
    if(body != NULL && body->IsActive() == true)
    {
        //        bool bodyState = body->IsActive();
        //        if(bodyState == false)
        //        {
        //            body->SetActive(true);
        //        }
        
        //Calculate b
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = body->GetFixtureList();
        while (fixture != NULL)
        {
            if(fixture->GetShape()->GetChildCount() <= 0)
            {
                break;
            }
            
            aabb.Combine(aabb, fixture->GetAABB(0));
            fixture = fixture->GetNext();
        }
        
        //        body->SetActive(bodyState);
        
        return aabb;
    }
    
    return b2AABB();
}

b2AABB Util::getFixtureBoundingBoxDynamic(b2Fixture* fixture)
{
    if(fixture != NULL && fixture->GetBody()->IsActive() == true)
    {
        //        bool bodyState = body->IsActive();
        //        if(bodyState == false)
        //        {
        //            body->SetActive(true);
        //        }
        
        //Calculate b
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        //        while (fixture != NULL)
        //        {
        aabb.Combine(aabb, fixture->GetAABB(0));
        fixture = fixture->GetNext();
        //        }
        
        //        body->SetActive(bodyState);
        
        return aabb;
    }
    
    return b2AABB();
    
}

b2Vec2 Util::getb2VecAnchor(b2Body* body, JointDef jointDef)
{
    if(body == NULL)
    {
        return b2Vec2(0,0);
    }
    //set joint anchor A
    b2AABB boundingBox = Util::getBodyBoundingBox(body);
    
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
    
    return jointAAnchor;
}

b2Vec2 Util::getb2VecAnchor(b2Fixture* fixture, JointDef jointDef)
{
    if(fixture == NULL)
    {
        return b2Vec2(0,0);
    }
    //set joint anchor A
    b2AABB boundingBox = Util::getFixtureBoundingBox(fixture);
    
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
    
    return jointAAnchor;
}

b2Vec2 Util::getb2VecAnchor(b2AABB aabb, JointDef jointDef)
{
    //set joint anchor A
    b2AABB boundingBox = aabb;
    
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
    
    return jointAAnchor;
}


void Util::setFixtureGroup(b2Fixture* fixture, uint16 group)
{
    if(fixture != NULL)
    {
        b2Filter filter = fixture->GetFilterData();
        //        filter.groupIndex = group;
        filter.categoryBits = group;
        switch (group) {
            case GROUP_A:
                filter.maskBits = GROUP_TOWER_B | GROUP_TERRAIN | GROUP_SKILL_DEFAULT | GROUP_MONSTER_SENSOR | GROUP_WALL;
                break;
            case GROUP_B:
                filter.maskBits = GROUP_TOWER_A | GROUP_TERRAIN| GROUP_SKILL_DEFAULT | GROUP_MONSTER_SENSOR | GROUP_WALL;
                break;
            case GROUP_NEUTRUAL:
                filter.maskBits = GROUP_TOWER_A | GROUP_TOWER_B | GROUP_TERRAIN | GROUP_SKILL_DEFAULT | GROUP_MONSTER_SENSOR;
                break;
            case GROUP_HERO_A:
                filter.maskBits = GROUP_TOWER_B| GROUP_TERRAIN | GROUP_SKILL_DEFAULT | GROUP_MONSTER_SENSOR |GROUP_ITEM | GROUP_WALL;
                break;
            case GROUP_HERO_B:
                filter.maskBits = GROUP_TOWER_A | GROUP_TERRAIN | GROUP_SKILL_DEFAULT | GROUP_MONSTER_SENSOR | GROUP_ITEM | GROUP_WALL;
                break;
            case GROUP_TERRAIN:
                filter.maskBits = 0xFFFFFF;
                break;
            case GROUP_SKILL_DEFAULT:
                filter.maskBits = 0xFFFFFF ^ GROUP_TERRAIN ^ GROUP_SENSOR ^ GROUP_SKILL_DEFAULT ^ GROUP_MONSTER_SENSOR;
                break;
            case GROUP_SENSOR:
                filter.maskBits = GROUP_TERRAIN;
                break;
            case GROUP_TOWER_A:
                //                filter.maskBits = GROUP_HERO_B | GROUP_B | GROUP_NEUTRUAL | GROUP_TERRAIN | GROUP_SKILL_DEFAULT| GROUP_MONSTER_SENSOR;
                filter.maskBits = GROUP_TERRAIN | GROUP_SKILL_DEFAULT| GROUP_MONSTER_SENSOR;
                break;
            case GROUP_TOWER_B:
                //                filter.maskBits = GROUP_HERO_A | GROUP_A | GROUP_NEUTRUAL | GROUP_TERRAIN | GROUP_SKILL_DEFAULT| GROUP_MONSTER_SENSOR;
                filter.maskBits = GROUP_TERRAIN | GROUP_SKILL_DEFAULT| GROUP_MONSTER_SENSOR;
                break;
            case GROUP_ITEM:
                filter.maskBits = GROUP_TERRAIN |GROUP_HERO_A | GROUP_HERO_B | GROUP_SKILL_DEFAULT | GROUP_WALL;
                break;
            case GROUP_WALL:
                filter.maskBits = GROUP_HERO_A | GROUP_HERO_B | GROUP_A | GROUP_B | GROUP_ITEM;
                break;
                
            default:
                break;
        }
        fixture->SetFilterData(filter);
    }
}

bool Util::bodiesAreTouching( b2Body* body1, b2Body* body2 )
{
    for (b2ContactEdge* edge = body1->GetContactList(); edge; edge = edge->next)
    {
        if ( !edge->contact->IsTouching() )
            continue;
        b2Body* bA = edge->contact->GetFixtureA()->GetBody();
        b2Body* bB = edge->contact->GetFixtureB()->GetBody();
        if ( ( bA == body1 && bB == body2 ) || ( bB == body1 && bA == body2 ) )
            return true;
    }
    return false;
}

bool Util::bodiesAreTouchingFixture( b2Body* body1, b2Fixture* fixture )
{
    for (b2ContactEdge* edge = body1->GetContactList(); edge; edge = edge->next)
    {
        if ( !edge->contact->IsTouching() )
            continue;
        b2Body* mbody = edge->contact->GetFixtureA()->GetBody();
        b2Fixture* mfixture = edge->contact->GetFixtureB();
        if (mbody == body1 && mfixture == fixture)
        {
            return true;
        }
        else
        {
            b2Body* mbody = edge->contact->GetFixtureB()->GetBody();
            b2Fixture* mfixture = edge->contact->GetFixtureA();
            if (mbody == body1 && mfixture == fixture)
            {
                return true;
            }
        }
    }
    return false;
}

bool Util::bodiesArePassingThrough( b2Body* body1, b2Body* body2 )
{
    for (b2ContactEdge* edge = body1->GetContactList(); edge; edge = edge->next)
    {
        if ( !edge->contact->IsTouching() )
            continue;
        b2Body* bA = edge->contact->GetFixtureA()->GetBody();
        b2Body* bB = edge->contact->GetFixtureB()->GetBody();
        if ( (( bA == body1 && bB == body2 ) || ( bB == body1 && bA == body2 )) && edge->contact->IsEnabled() == false )
        {
            return true;
        }
    }
    return false;
}


bool Util::fixtureArePassingThroughBody(b2Fixture* fixture, b2Body* body)
{
    //    for (b2ContactEdge* edge = fixture->GetBody()->GetContactList(); edge; edge = edge->next)
    //    {
    //        if ( !edge->contact->IsTouching())
    //            continue;
    //        b2Fixture* fix = edge->contact->GetFixtureA();
    //        b2Body* bB = edge->contact->GetFixtureB()->GetBody();
    //
    //        if((fix == fixture && bB == body) && edge->contact->IsEnabled() == false )
    //        {
    //
    //        }
    //
    //        if ( (( bA == body1 && bB == body2 ) || ( bB == body1 && bA == body2 )) && edge->contact->IsEnabled() == false )
    //        {
    //            return true;
    //        }
    //    }
    return false;
}


bool Util::bodiesAreTouchingWith(b2Body* body, int type)
{
    return false;
}

std::vector<string> Util::getStrTok(const char* text)
{
    std::vector<string> result;
    
    char* string = (char*)text;
    
    if(string != NULL)
    {
        const char s[3] = ", ";
        
        char *token;
        
        /* get the first token */
        token = std::strtok(string, s);
        
        /* walk through other tokens */
        while( token != NULL )
        {
            result.push_back(std::string(token));
            
            token = strtok(NULL, s);
        }
    }
    
    return result;
}

void Util::applyEffectFromList(vector<EffectData> listEffect, GameObject* object)
{
    for(int i=0 ; i<listEffect.size() ; i++)
    {
        int randomNum = Util::randomIntInRange(0, 100);
        if(randomNum <= listEffect[i].getChance())
        {
            Affect* affect = Affect::create();
            affect->setHolder(object);
            affect->setData(listEffect[i]);
        
            ((Character*)object)->applyAffect(affect);
        }
            // effect->isapplyed = true;
    }
}

ItemType Util::convertStringToItemType(const char* itemType)
{
    ItemType type = BONUS;
    
    if(strcasecmp(itemType, "container") == 0)
    {
        type = CONTAINER;
    }
    else if (strcasecmp(itemType, "bonus") == 0)
    {
        type = BONUS;
    }
    else if (strcasecmp(itemType, "gold") == 0)
    {
        type = GOLD;
    }
    else  {
        //nothing
    }
    
    return type;
}

XMLDataType Util::convertStringToXMLDataType(const char* xMLDataType)
{
    XMLDataType type = XML_UNKNOWN;
    
    if(strcasecmp(xMLDataType, "animation") == 0)
    {
        type = XML_ANIMATION;
    }
    else if (strcasecmp(xMLDataType, "tower") == 0)
    {
        type = XML_TOWER;
    }
    else if (strcasecmp(xMLDataType, "map") == 0)
    {
        type = XML_MAP;
    }
    else if (strcasecmp(xMLDataType, "hero") == 0)
    {
        type = XML_HERO;
    }
    else if (strcasecmp(xMLDataType, "item") == 0)
    {
        type = XML_ITEM;
    }
    else if (strcasecmp(xMLDataType, "monster") == 0)
    {
        type = XML_MONSTER;
    }
    else  {
        //nothing
    }
    
    return type;
}

vector<ItemStruct> Util::randomItemInList(vector<ItemStruct> listItemStruct, int count)
{
    vector<ItemStruct> listItemRandom;
    for (int i = 0; i < listItemStruct.size(); i++)
    {
        int chance = CCRANDOM_0_1()*100;
        if(chance <= listItemStruct[i].chance)
        {
            listItemRandom.push_back(listItemStruct[i]);
        }
    }
    
    vector<ItemStruct> listItem;
    
    for(int i = 0; i < count; i++)
    {
        int a = round(CCRANDOM_0_1()*(listItemRandom.size()-1));
        if(a < listItemRandom.size())
        {
            listItem.push_back(listItemRandom[a]);
        }
        
    }
    
    return listItem;
}

float Util::randomFloatInRange(float lowerBound, float upperBound)
{
    return (lowerBound + (upperBound-lowerBound)*CCRANDOM_0_1());
}

float Util::randomIntInRange(int lowerBound, int upperBound)
{
    return (lowerBound + (upperBound-lowerBound)*CCRANDOM_0_1());
}

b2Fixture* Util::getFixtureById(b2Body* body, FixtureID fixtureId)
{
    for(b2Fixture* f = body->GetFixtureList(); f;f=f->GetNext())
    {
        PhysicData* data = (PhysicData*)f->GetUserData();
        if(data->fixtureId == fixtureId)
        {
            return f;
        }
    }
    return NULL;
}

b2AABB Util::getGameObjectBoundingBox(GameObject* obj)
{
    if(obj->getBody() != NULL&& obj->getBody()->IsActive() == true)
    {
        //Calculate b
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = obj->getBody()->GetFixtureList();
        while (fixture != NULL)
        {
            PhysicData* data = (PhysicData*) fixture->GetUserData();
            if(data != NULL && obj->isBodyFixture(data->fixtureId)==true)
            {
                b2Transform t;
                t.SetIdentity();
                const b2Shape *shape = fixture->GetShape();
                const int childCount = shape->GetChildCount();
                for (int child = 0; child < childCount; ++child)
                {
                    const b2Vec2 r(shape->m_radius, shape->m_radius);
                    b2AABB shapeAABB;
                    shape->ComputeAABB(&shapeAABB, t, child);
                    shapeAABB.lowerBound = shapeAABB.lowerBound + r;
                    shapeAABB.upperBound = shapeAABB.upperBound - r;
                    aabb.Combine(shapeAABB);
                }
                
            }
            fixture = fixture->GetNext();
        }
        return aabb;
    }
    
    
    return b2AABB();
}

b2AABB Util::getGameObjectBoundingBoxDynamic(GameObject* obj)
{
    if(obj->getBody() != NULL && obj->getBody()->IsActive() == true)
    {
        //Calculate b
        b2AABB aabb;
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = obj->getBody()->GetFixtureList();
        while (fixture != NULL)
        {
            PhysicData* data = (PhysicData*) fixture->GetUserData();
            if(data != NULL && obj->isBodyFixture(data->fixtureId)==true)
            {
                aabb.Combine(aabb, fixture->GetAABB(0));
            }
            fixture = fixture->GetNext();
        }
        return aabb;
    }
    return b2AABB();
}

CCAnimation* Util::getAnimationFromListFrameName(vector<string> listFrameName, unsigned int loops,float delayPerUnit)
{
    CCAnimation* animation = CCAnimation::create();
    
    for(int i = 0; i < listFrameName.size(); i++)
    {
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(listFrameName[i].c_str()));
    }
    
    animation->setLoops(loops);
    animation->setDelayPerUnit(delayPerUnit);
    return animation;
}


CCAnimation* Util::getAnimationFromAnimationObject(AnimationObject* animationObject)
{
    CCAnimation* animation = CCAnimation::create();
    
    for(int i = 0; i < animationObject->getListFrameName().size(); i++)
    {
        CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(animationObject->getListFrameName()[i].c_str());
        if(spriteFrame)
        {
            animation->addSpriteFrame(spriteFrame);
        }
        
    }
    
    animation->setLoops(animationObject->getLoops());
    animation->setDelayPerUnit(animationObject->getDelayPerUnit());
    return animation;
}

void Util::pauseNodeAndItsChild(CCNode* node)
{
    if(node != NULL)
    {
        CCArray* listChild = node->getChildren();
        CCObject* child;
        CCARRAY_FOREACH(listChild, child)
        {
            Util::pauseNodeAndItsChild((CCNode*)child);
        }
        node->pauseSchedulerAndActions();
    }
}

void Util::resumeNodeAndItsChild(CCNode* node)
{
    if(node != NULL)
    {
        CCArray* listChild = node->getChildren();
        CCObject* child;
        CCARRAY_FOREACH(listChild, child)
        {
            Util::resumeNodeAndItsChild((CCNode*)child);
        }
        node->resumeSchedulerAndActions();
    }
}

bool Util::checkPointIsInViewPort(CCPoint point, CCNode* node)
{
    CCPoint zero = node->convertToNodeSpace(ccp(0,0));
//    CCSize size = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
//    CCLOG("zero(%f,%f)",zero.x,zero.y);
//    CCLOG("max(%f,%f)",size.width,size.height);
//    CCLOG("point(%f,%f)",point.x,point.y);
    
    CCRect rect = CCRect(zero.x, zero.y, size.width, size.height);
//    CCLOG("%d",rect.containsPoint(point));
    return rect.containsPoint(point);
}

string Util::convertTime(int s)
{
    int minute = s / 60;
    int second = s - minute*60;
    
    return CCString::createWithFormat("%02d:%02d", minute, second)->getCString();
}
